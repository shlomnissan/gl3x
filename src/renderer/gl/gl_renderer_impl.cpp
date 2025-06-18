/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_renderer_impl.hpp"

#include "gleam/core/fog.hpp"
#include "gleam/lights/ambient_light.hpp"
#include "gleam/lights/directional_light.hpp"
#include "gleam/lights/point_light.hpp"
#include "gleam/lights/spot_light.hpp"
#include "gleam/materials/flat_material.hpp"
#include "gleam/materials/phong_material.hpp"
#include "gleam/materials/shader_material.hpp"
#include "gleam/math/vector3.hpp"

#include "core/render_lists.hpp"
#include "core/program_attributes.hpp"
#include "utilities/logger.hpp"

#include <array>
#include <cmath>
#include <utility>

#include <glad/glad.h>

namespace gleam {

namespace {

static const auto light_uniforms = std::array<std::string, 9> {
    "u_Lights[0]",
    "u_Lights[1]",
    "u_Lights[2]",
    "u_Lights[3]",
    "u_Lights[4]",
    "u_Lights[5]",
    "u_Lights[6]",
    "u_Lights[7]",
    "u_Lights[8]",
};

}

Renderer::Impl::Impl(const Renderer::Parameters& params)
  : params_(params),
    render_lists_(std::make_unique<RenderLists>()) {
    state_.SetViewport(0, 0, params.width, params.height);
}

auto Renderer::Impl::RenderObjects(Scene* scene, Camera* camera) -> void {
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

    auto geometry = mesh->geometry.get();
    auto material = mesh->material.get();

    auto attrs = ProgramAttributes {material, render_lists_.get(), scene};
    auto program = programs_.GetProgram(attrs);
    if (!program->IsValid()) {
        return;
    }

    state_.ProcessMaterial(material);

    if (attrs.lights && !render_lists_->Lights().empty()) {
        UpdateLights(program, camera);
    }

    buffers_.Bind(mesh->geometry);

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
    auto material = mesh->material.get();
    auto model = mesh->GetWorldTransform();
    auto resolution = Vector2(params_.width, params_.height);

    program->SetUniform(Uniform::Projection, &camera->projection_transform);
    program->SetUniform(Uniform::Model, &model);
    program->SetUniform(Uniform::View, &camera->view_transform);
    program->SetUniform(Uniform::Opacity, &material->opacity);
    program->SetUniform(Uniform::Resolution, &resolution);

    if (auto fog = scene->fog.get()) {
        auto type = fog->GetType();
        program->SetUniform(Uniform::FogType, &type);
        if (type == FogType::LinearFog) {
            auto f = static_cast<LinearFog*>(fog);
            program->SetUniform(Uniform::FogColor, &f->color);
            program->SetUniform(Uniform::FogNear, &f->near);
            program->SetUniform(Uniform::FogFar, &f->near);
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
        if (attrs->directional_lights || attrs->point_lights || attrs->spot_lights) {
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

auto Renderer::Impl::UpdateLights(GLProgram* program, const Camera* camera) const -> void {
    auto ambient_light = Color {0.0f, 0.0f, 0.0f};
    auto idx = 0;

    for (auto light : render_lists_->Lights()) {
        const auto light_color = light->color;
        const auto intensity = light->intensity;
        const auto type = light->GetType();
        const auto& uniform = light_uniforms[idx];

        if (type == LightType::AmbientLight) {
            ambient_light = light_color * intensity;
        } else {
            program->SetUnknownUniform(uniform + ".Type", &type);
        }

        if (type == LightType::DirectionalLight) {
            auto l = static_cast<DirectionalLight*>(light);
            const auto direction = Vector3(camera->view_transform * Vector4(l->Direction(), 0.0f));
            const auto color = l->color * l->intensity;
            program->SetUnknownUniform(uniform + ".Color", &color);
            program->SetUnknownUniform(uniform + ".Direction", &direction);
            ++idx;
        }

        if (type == LightType::PointLight) {
            auto l = static_cast<PointLight*>(light);
            const auto color = l->color * l->intensity;
            const auto position = Vector3(camera->view_transform * Vector4(light->GetWorldPosition(), 1.0f));
            program->SetUnknownUniform(uniform + ".Color", &color);
            program->SetUnknownUniform(uniform + ".Position", &position);
            program->SetUnknownUniform(uniform + ".Base", &l->attenuation.base);
            program->SetUnknownUniform(uniform + ".Linear", &l->attenuation.linear);
            program->SetUnknownUniform(uniform + ".Quadratic", &l->attenuation.quadratic);
            ++idx;
        }

        if (type == LightType::SpotLight) {
            auto l = static_cast<SpotLight*>(light);
            const auto direction = Vector3(camera->view_transform * Vector4(l->Direction(), 0.0f));
            const auto position = Vector3(camera->view_transform * Vector4(light->GetWorldPosition(), 1.0f));
            const auto color = l->color * l->intensity;
            const auto cone_cos = std::cos(l->angle);
            const auto penumbra_cos = std::cos(l->angle * (1 - l->penumbra));
            program->SetUnknownUniform(uniform + ".Color", &color);
            program->SetUnknownUniform(uniform + ".Direction", &direction);
            program->SetUnknownUniform(uniform + ".Position", &position);
            program->SetUnknownUniform(uniform + ".ConeCos", &cone_cos);
            program->SetUnknownUniform(uniform + ".PenumbraCos", &penumbra_cos);
            program->SetUnknownUniform(uniform + ".Base", &l->attenuation.base);
            program->SetUnknownUniform(uniform + ".Linear", &l->attenuation.linear);
            program->SetUnknownUniform(uniform + ".Quadratic", &l->attenuation.quadratic);
            ++idx;
        }
    }

    program->SetUniform(Uniform::AmbientLight, &ambient_light);
}

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->UpdateTransformHierarchy();
    camera->SetViewTransform();

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
    auto geometry = mesh->geometry;

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
    auto bounding_sphere = mesh->geometry->BoundingSphere();
    bounding_sphere.ApplyTransform(mesh->GetWorldTransform());
    return frustum_.IntersectsWithSphere(bounding_sphere);
}

Renderer::Impl::~Impl() = default;

}