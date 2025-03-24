// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "renderer/gl/gl_renderer_impl.hpp"

#include "engine/core/fog.hpp"
#include "engine/lights/ambient_light.hpp"
#include "engine/lights/directional_light.hpp"
#include "engine/lights/point_light.hpp"
#include "engine/lights/spot_light.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/materials/shader_material.hpp"
#include "engine/math/vector3.hpp"

#include "core/render_lists.hpp"
#include "core/program_attributes.hpp"
#include "utilities/logger.hpp"

#include <cmath>
#include <format>

#include <glad/glad.h>

namespace engine {

Renderer::Impl::Impl(const Renderer::Parameters& params)
  : params_(params),
    render_lists_(std::make_unique<RenderLists>()) {
    state_.SetViewport(0, 0, params.width, params.height);
}

auto Renderer::Impl::RenderObjects(Scene* scene, Camera* camera) -> void {
    frustum_.SetWithViewProjection(camera->projection_transform * camera->view_transform);

    for (auto weak_mesh : render_lists_->Opaque()) {
        if (auto mesh = weak_mesh.lock()) {
            RenderMesh(mesh.get(), scene, camera);
        }
    }

    for (auto weak_mesh : render_lists_->Transparent()) {
        if (auto mesh = weak_mesh.lock()) {
            RenderMesh(mesh.get(), scene, camera);
        }
    }

    rendered_objects_per_frame_ = rendered_objects_counter_;
    rendered_objects_counter_ = 0;
}

auto Renderer::Impl::RenderMesh(Mesh* mesh, Scene* scene, Camera* camera) -> void {
    auto geometry = mesh->GetGeometry();
    auto material = mesh->GetMaterial();

    if (!IsValidMesh(mesh)) return;
    if (!IsVisible(mesh)) return;

    auto attrs = ProgramAttributes {material, render_lists_.get(), scene};
    auto program = programs_.GetProgram(attrs);
    if (!program->IsValid()) {
        return;
    }

    state_.ProcessMaterial(material);

    if (attrs.lights && !render_lists_->Lights().empty()) {
        UpdateLights(scene, program, camera);
    }

    buffers_.Bind(geometry);

    SetUniforms(program, &attrs, mesh, camera, scene);

    program->Use();
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
    auto material = mesh->GetMaterial();
    auto model_view = camera->view_transform * mesh->GetWorldTransform();

    // Shared uniforms
    // ----------------
    // These uniforms are shared across all materials. They are set only if they exist in
    // the shader source code to support custom shaders that may choose not to use them.

    program->SetUniformIfExists("u_Projection", camera->projection_transform);
    program->SetUniformIfExists("u_ModelView", model_view);
    program->SetUniformIfExists("u_Opacity", material->opacity);
    program->SetUniformIfExists("u_Resolution", Vector2(params_.width, params_.height));

    if (attrs->linear_fog) {
        const auto linear_fog = scene->fog->As<LinearFog>();
        program->SetUniformIfExists("u_LinearFog.Color", linear_fog->color);
        program->SetUniformIfExists("u_LinearFog.Near", linear_fog->near);
        program->SetUniformIfExists("u_LinearFog.Far", linear_fog->far);
    }

    if (attrs->exponential_fog) {
        const auto exponential_fog = scene->fog->As<ExponentialFog>();
        program->SetUniformIfExists("u_ExponentialFog.Color", exponential_fog->color);
        program->SetUniformIfExists("u_ExponentialFog.Density", exponential_fog->density);
    }

    // Material specific uniforms
    // ----------------
    // These uniforms are specific to the material type. These uniforms are always
    // expected to be used in the shader source code that corresponds to the material type.

    if (attrs->type == MaterialType::FlatMaterial) {
        auto m = material->As<FlatMaterial>();
        program->SetUniform("u_Color", m->color);
        if (attrs->texture_map) {
            program->SetUniform("u_TextureMap", 0);
            program->SetUniform("u_TextureTransform", m->texture_map->transform.Get());
            textures_.Bind(m->texture_map.get());
        }
    }

    if (attrs->type == MaterialType::PhongMaterial) {
        auto m = material->As<PhongMaterial>();
        program->SetUniform("u_Color", m->color);
        if (attrs->directional_lights || attrs->point_lights || attrs->spot_lights) {
            program->SetUniform("u_Specular", m->specular);
            program->SetUniform("u_Shininess", m->shininess);
            if (!attrs->flat_shaded) {
                // The normal matrix is optimized away in flat shaded mode.
                program->SetUniformIfExists("u_NormalMatrix", Transpose(Inverse(Matrix3(model_view))));
            }
        }

        if (attrs->texture_map) {
            program->SetUniform("u_TextureMap", 0);
            program->SetUniform("u_TextureTransform", m->texture_map->transform.Get());
            textures_.Bind(m->texture_map.get());
        }
    }

    if (attrs->type == MaterialType::ShaderMaterial) {
        auto m = material->As<ShaderMaterial>();
        for (const auto& [name, value] : m->uniforms) {
            program->SetUniform(name, value);
        }
    }
}

auto Renderer::Impl::UpdateLights(const Scene* scene, GLProgram* program, const Camera* camera) const -> void {
    auto ambient_light = Color {0.0f, 0.0f, 0.0f};
    auto directional_idx = 0;
    auto point_idx = 0;
    auto spot_idx = 0;

    for (auto weak_light : render_lists_->Lights()) {
        if (auto light = weak_light.lock()) {
            const auto color = light->color;
            const auto intensity = light->intensity;

            if (auto ambient = light->As<AmbientLight>()) {
                ambient_light.r += color.r * intensity;
                ambient_light.g += color.g * intensity;
                ambient_light.b += color.b * intensity;
            }

            if (auto directional = light->As<DirectionalLight>()) {
                const auto u_name = std::format("u_DirectionalLights[{}]", directional_idx);
                const auto u_dir = camera->view_transform * Vector4(directional->Direction(), 0.0f);
                const auto u_color = directional->color * directional->intensity;
                program->SetUniform(u_name + ".Color", u_color);
                program->SetUniform(u_name + ".Direction", Vector3(u_dir));
                directional_idx++;
            }

            if (auto point = light->As<PointLight>()) {
                const auto u_name = std::format("u_PointLights[{}]", point_idx);
                const auto u_pos = camera->view_transform * Vector4(light->GetWorldPosition(), 1.0f);
                const auto u_color = point->color * point->intensity;
                program->SetUniform(u_name + ".Color", u_color);
                program->SetUniform(u_name + ".Position", u_pos);
                point_idx++;
            }

            if (auto spot = light->As<SpotLight>()) {
                const auto u_name = std::format("u_SpotLights[{}]", spot_idx);
                const auto u_dir = camera->view_transform * Vector4(spot->Direction(), 0.0f);
                const auto u_pos = camera->view_transform * Vector4(light->GetWorldPosition(), 1.0f);
                const auto u_color = spot->color * spot->intensity;
                program->SetUniform(u_name + ".Color", u_color);
                program->SetUniform(u_name + ".Direction", Vector3(u_dir));
                program->SetUniform(u_name + ".Position", u_pos);
                program->SetUniform(u_name + ".ConeCos", std::cos(spot->angle));
                program->SetUniform(u_name + ".PenumbraCos", std::cos(spot->angle * (1 - spot->penumbra)));
                spot_idx++;
            }
        }
    }

    program->SetUniform("u_AmbientLight", ambient_light);
}

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->UpdateTransformHierarchy();
    camera->UpdateViewTransform();

    if (scene->touched_) {
        render_lists_->ProcessScene(scene);
        scene->touched_ = false;
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