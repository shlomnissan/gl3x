/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_renderer_impl.hpp"

#include "gleam/materials/phong_material.hpp"
#include "gleam/materials/shader_material.hpp"
#include "gleam/materials/sprite_material.hpp"
#include "gleam/materials/unlit_material.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/nodes/fog.hpp"
#include "gleam/nodes/instanced_mesh.hpp"
#include "gleam/nodes/sprite.hpp"

#include "core/program_attributes.hpp"
#include "core/render_lists.hpp"
#include "utilities/logger.hpp"

#include <glad/glad.h>

namespace gleam {

Renderer::Impl::Impl(const Renderer::Parameters& params)
  : params_(params),
    render_lists_(std::make_unique<RenderLists>()) {
    state_.SetViewport(0, 0, params.framebuffer_width, params.framebuffer_height);
    state_.SetClearColor(params.clear_color);
}

auto Renderer::Impl::Initialize() -> std::expected<void, std::string> {
    // no-op, nothing to initialize
    return {};
}

auto Renderer::Impl::RenderObjects(Scene* scene, Camera* camera) -> void {
    camera_ubo_.Update(camera->projection_matrix, camera->view_matrix);

    for (auto renderable : render_lists_->Opaque()) {
        RenderObject(renderable, scene, camera);
    }

    if (!render_lists_->Transparent().empty()) state_.SetDepthMask(false);
    for (auto renderable : render_lists_->Transparent()) {
        RenderObject(renderable, scene, camera);
    }

    state_.SetDepthMask(true);

    rendered_objects_per_frame_ = rendered_objects_counter_;
    rendered_objects_counter_ = 0;
}

auto Renderer::Impl::RenderObject(Renderable* renderable, Scene* scene, Camera* camera) -> void {
    auto geometry = renderable->GetGeometry().get();
    auto material = renderable->GetMaterial().get();
    auto attrs = ProgramAttributes {renderable, {
        .directional = lights_.directional,
        .point = lights_.point,
        .spot = lights_.spot
    }, scene};

    auto program = programs_.GetProgram(attrs);
    if (!program->IsValid()) {
        return;
    }

    state_.ProcessMaterial(material);
    if (material->wireframe && Renderable::IsMeshType(renderable)) {
        const auto mesh = static_cast<Mesh*>(renderable);
        buffers_.Bind(mesh->GetWireframeGeometry());
        geometry = mesh->GetWireframeGeometry().get();
    } else {
        buffers_.Bind(renderable->GetGeometry());
    }

    SetUniforms(program, &attrs, renderable, camera, scene);

    state_.UseProgram(program->Id());
    program->UpdateUniforms();

    auto primitive = GL_TRIANGLES;
    if (geometry->primitive == GeometryPrimitiveType::Lines) {
        primitive = GL_LINES;
    }
    if (geometry->primitive == GeometryPrimitiveType::LineLoop) {
        primitive = GL_LINE_LOOP;
    }

    const auto index_size = geometry->IndexData().size();
    const auto vertex_size = geometry->VertexCount();

    if (renderable->GetNodeType() != NodeType::InstancedMeshNode) {
        index_size
            ? glDrawElements(primitive, index_size, GL_UNSIGNED_INT, nullptr)
            : glDrawArrays(primitive, 0, vertex_size);
    }

    if (renderable->GetNodeType() == NodeType::InstancedMeshNode) {
        const auto instanced = static_cast<InstancedMesh*>(renderable);
        const auto count = instanced->Count();
        buffers_.BindInstancedMesh(instanced);

        index_size
            ? glDrawElementsInstanced(primitive, index_size, GL_UNSIGNED_INT, nullptr, count)
            : glDrawArraysInstanced(primitive, 0, vertex_size, count);
    }

    rendered_objects_counter_++;
}

auto Renderer::Impl::SetUniforms(
    GLProgram* program,
    ProgramAttributes* attrs,
    Renderable* renderable,
    Camera* camera,
    Scene* scene
) -> void {
    auto material = renderable->GetMaterial().get();
    auto model = renderable->GetWorldTransform();
    auto resolution = Vector2(
        params_.framebuffer_width,
        params_.framebuffer_height
    );

    program->SetUniform(Uniform::Model, &model);
    program->SetUniform(Uniform::Opacity, &material->opacity);
    program->SetUniform(Uniform::Resolution, &resolution);

    if (auto fog = scene->fog.get()) {
        auto type = fog->GetType();
        program->SetUniform(Uniform::FogType, &type);
        if (type == FogType::LinearFog) {
            auto f = static_cast<LinearFog*>(fog);
            program->SetUniform(Uniform::FogColor, &f->color);
            program->SetUniform(Uniform::FogNear, &f->near);
            program->SetUniform(Uniform::FogFar, &f->far);
        }

        if (type == FogType::ExponentialFog) {
            auto f = static_cast<ExponentialFog*>(fog);
            program->SetUniform(Uniform::FogColor, &f->color);
            program->SetUniform(Uniform::FogDensity, &f->density);
        }
    }

    if (attrs->type == MaterialType::PhongMaterial) {
        auto m = static_cast<PhongMaterial*>(material);
        if (lights_.HasLights()) {
            program->SetUniform(Uniform::AmbientLight, &lights_.ambient_light);
            program->SetUniform(Uniform::MaterialDiffuseColor, &m->color);
            program->SetUniform(Uniform::MaterialSpecularColor, &m->specular);
            program->SetUniform(Uniform::MaterialShininess, &m->shininess);
        }

        if (attrs->albedo_map) {
            auto map_type = GLTextureMapType::AlbedoMap;
            textures_.Bind(m->albedo_map, map_type);
            const auto& transform = m->albedo_map->GetTransform();
            program->SetUniform(Uniform::AlbedoMap, &map_type);
            program->SetUniform(Uniform::TextureTransform, &transform);
        }

        if (attrs->alpha_map) {
            auto map_type = GLTextureMapType::AlphaMap;
            textures_.Bind(m->alpha_map, map_type);
            program->SetUniform(Uniform::AlphaMap, &map_type);
        }
    }

    if (attrs->type == MaterialType::ShaderMaterial) {
        auto m = static_cast<ShaderMaterial*>(material);
        for (const auto& [name, value] : m->uniforms) {
            program->SetUnknownUniform(name, &value);
        }
    }

    if (attrs->type == MaterialType::SpriteMaterial) {
        auto m = static_cast<SpriteMaterial*>(material);
        auto r = static_cast<Sprite*>(renderable);

        program->SetUniform(Uniform::Anchor, &r->anchor);
        program->SetUniform(Uniform::Color, &m->color);
        program->SetUniform(Uniform::Rotation, &r->rotation);

        if (attrs->albedo_map) {
            auto map_type = GLTextureMapType::AlbedoMap;
            textures_.Bind(m->albedo_map, map_type);
            const auto& transform = m->albedo_map->GetTransform();
            program->SetUniform(Uniform::AlbedoMap, &map_type);
            program->SetUniform(Uniform::TextureTransform, &transform);
        }

        if (attrs->alpha_map) {
            auto map_type = GLTextureMapType::AlphaMap;
            textures_.Bind(m->alpha_map, map_type);
            program->SetUniform(Uniform::AlphaMap, &map_type);
        }
    }

    if (attrs->type == MaterialType::UnlitMaterial) {
        auto m = static_cast<UnlitMaterial*>(material);
        program->SetUniform(Uniform::Color, &m->color);

        if (attrs->albedo_map) {
            auto map_type = GLTextureMapType::AlbedoMap;
            textures_.Bind(m->albedo_map, map_type);
            const auto& transform = m->albedo_map->GetTransform();
            program->SetUniform(Uniform::AlbedoMap, &map_type);
            program->SetUniform(Uniform::TextureTransform, &transform);
        }

        if (attrs->alpha_map) {
            auto map_type = GLTextureMapType::AlphaMap;
            textures_.Bind(m->alpha_map, map_type);
            program->SetUniform(Uniform::AlphaMap, &map_type);
        }
    }
}

auto Renderer::Impl::ProcessLights(Camera* camera) -> void {
    lights_.Reset();

    for(auto light : render_lists_->Lights()) {
        lights_.AddLight(light, camera);
    }

    if (lights_.HasLights()) lights_.Update();
}

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->UpdateTransformHierarchy();
    camera->UpdateViewMatrix();

    render_lists_->ProcessScene(scene, camera);
    ProcessLights(camera);

    RenderObjects(scene, camera);
}

auto Renderer::Impl::SetViewport(int x, int y, int width, int height) -> void {
    state_.SetViewport(x, y, width, height);
}

auto Renderer::Impl::SetClearColor(const Color& color) -> void {
    state_.SetClearColor(color);
}

Renderer::Impl::~Impl() = default;

}