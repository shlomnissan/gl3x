/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_renderer_impl.hpp"

#include "gleam/materials/flat_material.hpp"
#include "gleam/materials/phong_material.hpp"
#include "gleam/materials/shader_material.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/nodes/fog.hpp"

#include "core/render_lists.hpp"
#include "core/program_attributes.hpp"
#include "utilities/logger.hpp"

#include <array>
#include <cmath>
#include <utility>

#include <glad/glad.h>

namespace gleam {

Renderer::Impl::Impl(const Renderer::Parameters& params)
  : params_(params),
    render_lists_(std::make_unique<RenderLists>()) {
    state_.SetViewport(0, 0, params.width, params.height);
}

auto Renderer::Impl::RenderObjects(Scene* scene, Camera* camera) -> void {
    camera_.Update(camera->projection_transform, camera->view_transform);
    frustum_.SetWithViewProjection(camera->projection_transform * camera->view_transform);

    for (auto mesh : render_lists_->Opaque()) {
        RenderMesh(mesh, scene, camera);
    }

    if (!render_lists_->Transparent().empty()) state_.SetDepthMask(false);
    for (auto mesh : render_lists_->Transparent()) {
        RenderMesh(mesh, scene, camera);
    }

    state_.SetDepthMask(true);

    rendered_objects_per_frame_ = rendered_objects_counter_;
    rendered_objects_counter_ = 0;
}

auto Renderer::Impl::RenderMesh(Mesh* mesh, Scene* scene, Camera* camera) -> void {
    if (!IsValidMesh(mesh)) return;
    if (!IsVisible(mesh)) return;

    auto geometry = mesh->GetGeometry().get();
    auto material = mesh->GetMaterial().get();

    auto attrs = ProgramAttributes {material, {
        .directional = lights_.directional,
        .point = lights_.point,
        .spot = lights_.spot
    }, scene};
    auto program = programs_.GetProgram(attrs);
    if (!program->IsValid()) {
        return;
    }

    state_.ProcessMaterial(material);
    if (material->wireframe) {
        buffers_.Bind(mesh->GetWireframeGeometry());
        geometry = mesh->GetWireframeGeometry().get();
    } else {
        buffers_.Bind(mesh->GetGeometry());
    }

    SetUniforms(program, &attrs, mesh, camera, scene);

    state_.UseProgram(program->Id());
    program->UpdateUniforms();

    auto primitive = GL_TRIANGLES;
    if (geometry->primitive == GeometryPrimitiveType::Lines) {
        primitive = GL_LINES;
    }
    if (geometry->primitive == GeometryPrimitiveType::LineLoop) {
        primitive = GL_LINE_LOOP;
    }

    if (geometry->IndexData().empty()) {
        glDrawArrays(primitive, 0, geometry->VertexCount());
    } else {
        glDrawElements(
            primitive,
            geometry->IndexData().size(),
            GL_UNSIGNED_INT,
            nullptr
        );
    }

    rendered_objects_counter_++;
}

auto Renderer::Impl::SetUniforms(
    GLProgram* program,
    ProgramAttributes* attrs,
    Mesh* mesh,
    Camera* camera,
    Scene* scene
) -> void {
    auto material = mesh->GetMaterial().get();
    auto model = mesh->GetWorldTransform();
    auto resolution = Vector2(params_.width, params_.height);

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

    if (attrs->type == MaterialType::FlatMaterial) {
        auto m = static_cast<FlatMaterial*>(material);
        program->SetUniform(Uniform::Color, &m->color);
        if (attrs->texture_map) {
            const auto& transform = m->texture_map->GetTransform();
            program->SetUniform(Uniform::TextureMap, 0);
            program->SetUniform(Uniform::TextureTransform, &transform);
            textures_.Bind(m->texture_map);
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

        if (attrs->texture_map) {
            const auto& transform = m->texture_map->GetTransform();
            program->SetUniform(Uniform::TextureMap, 0);
            program->SetUniform(Uniform::TextureTransform, &transform);
            textures_.Bind(m->texture_map);
        }
    }

    if (attrs->type == MaterialType::ShaderMaterial) {
        auto m = static_cast<ShaderMaterial*>(material);
        for (const auto& [name, value] : m->uniforms) {
            program->SetUnknownUniform(name, &value);
        }
    }
}

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->UpdateTransformHierarchy();
    camera->SetViewTransform();

    if (scene->touched_) {
        render_lists_->ProcessScene(scene);
        scene->touched_ = false;
    }

    lights_.Reset();
    for(auto light : render_lists_->Lights()) lights_.AddLight(light, camera);
    if (lights_.HasLights()) {
        lights_.Update();
    }

    RenderObjects(scene, camera);
}

auto Renderer::Impl::SetClearColor(const Color& color) -> void {
    state_.SetClearColor(color);
}

auto Renderer::Impl::IsValidMesh(Mesh* mesh) const -> bool {
    auto geometry = mesh->GetGeometry();

    if (geometry->Disposed()) {
        Logger::Log(LogLevel::Warning,
            "Skipped rendering a mesh with disposed geometry {}", *mesh
        );
        return false;
    }

    if (geometry->VertexData().empty()) {
        Logger::Log(LogLevel::Warning,
            "Skipped rendering a mesh with no geometry data {}", *mesh
        );
        return false;
    }

    if (geometry->Attributes().empty()) {
        Logger::Log(LogLevel::Warning,
            "Skipped rendering a mesh with no geometry attributes {}", *mesh
        );
        return false;
    }

    return true;
}

auto Renderer::Impl::IsVisible(Mesh* mesh) const -> bool {
    auto bounding_sphere = mesh->GetGeometry()->BoundingSphere();
    bounding_sphere.ApplyTransform(mesh->GetWorldTransform());
    return frustum_.IntersectsWithSphere(bounding_sphere);
}

Renderer::Impl::~Impl() = default;

}