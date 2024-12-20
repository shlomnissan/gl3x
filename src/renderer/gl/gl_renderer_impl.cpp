// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_renderer_impl.hpp"

#include "engine/core/logger.hpp"
#include "engine/lights/ambient_light.hpp"
#include "engine/lights/directional_light.hpp"
#include "engine/lights/point_light.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/materials/phong_material.hpp"
#include "engine/math/vector3.hpp"

#include "core/program_attributes.hpp"

#include <glad/glad.h>

namespace engine {

Renderer::Impl::Impl(const Renderer::Parameters& params) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, params.width, params.height);
}

auto Renderer::Impl::RenderObjects(Node* node, Scene* scene, Camera* camera) -> void {
    for (const auto node : node->Children()) {
        if (node->Is<Mesh>()) {
            auto mesh = node->As<Mesh>();
            auto geometry = mesh->GetGeometry();
            auto material = mesh->GetMaterial();

            if (!IsValidMesh(mesh)) continue;

            auto attrs = ProgramAttributes {material, scene};
            auto program = programs_.GetProgram(attrs);
            if (!program->IsValid()) {
                return;
            }

            // Handle backface culling
            if (curr_backface_culling_mode != material->cull_backfaces) {
                material->cull_backfaces ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
                curr_backface_culling_mode = material->cull_backfaces;
            }

            // Handle wireframe mode
            if (curr_wireframe_mode_ != material->wireframe) {
                material->wireframe
                    ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
                    : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                curr_wireframe_mode_ = material->wireframe;
            }

            // Handle polygon offset
            if (material->polygon_offset.has_value()) {
                glEnable(GL_POLYGON_OFFSET_FILL);
                glPolygonOffset(
                    material->polygon_offset->factor,
                    material->polygon_offset->units
                );
            } else {
                glDisable(GL_POLYGON_OFFSET_FILL);
            }

            if (attrs.lights) UpdateLights(scene, program, camera);

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
        }

        RenderObjects(node.get(), scene, camera);
    }
}

auto Renderer::Impl::SetUniforms(
    GLProgram* program,
    ProgramAttributes* attrs,
    Mesh* mesh,
    Camera* camera,
    Scene* scene
) -> void {
    auto material = mesh->GetMaterial();
    auto model_view = camera->view_transform * mesh->world_transform.Get();

    program->SetUniform("u_Projection", camera->projection_transform.Get());
    program->SetUniform("u_ModelView", model_view);

    if (attrs->type == MaterialType::kFlatMaterial) {
        auto m = material->As<FlatMaterial>();
        program->SetUniform("u_Color", m->color);
        if (attrs->texture_map) {
            program->SetUniform("u_TextureMap", 0);
            program->SetUniform("u_TextureTransform", m->texture_map->transform.Get());
            textures_.Bind(m->texture_map.get());
        }
    }

    if (attrs->type == MaterialType::kPhongMaterial) {
        auto m = material->As<PhongMaterial>();
        program->SetUniform("u_Diffuse", m->color);

        if (attrs->directional_lights || attrs->point_lights || attrs->spot_lights) {
            program->SetUniform("u_Specular", m->specular);
            program->SetUniform("u_Shininess", m->shininess);
            program->SetUniform("u_NormalMatrix", Transpose(Inverse(Matrix3(model_view))));
        }

        if (attrs->texture_map) {
            program->SetUniform("u_TextureMap", 0);
            program->SetUniform("u_TextureTransform", m->texture_map->transform.Get());
            textures_.Bind(m->texture_map.get());
        }
    }

    if (attrs->fog) {
        program->SetUniform("u_Fog.Color", scene->fog.value().color);
        program->SetUniform("u_Fog.Near", scene->fog.value().near);
        program->SetUniform("u_Fog.Far", scene->fog.value().far);
    }
}

auto Renderer::Impl::UpdateLights(const Scene* scene, GLProgram* program, const Camera* camera) const -> void {
    auto ambient_light = Color {0.0f, 0.0f, 0.0f};
    auto directional_idx = 0;
    auto point_idx = 0;

    for (auto weak_light : scene->Lights()) {
        if (auto light = weak_light.lock()) {
            const auto color = light->color;
            const auto intensity = light->intensity;

            if (auto ambient = light->As<AmbientLight>()) {
                ambient_light.r += color.r * intensity;
                ambient_light.g += color.g * intensity;
                ambient_light.b += color.b * intensity;
            }

            if (auto directional = light->As<DirectionalLight>()) {
                const auto u_name = fmt::format("u_DirectionalLights[{}]", directional_idx);
                const auto u_dir = camera->view_transform * Vector4(directional->Direction(), 0.0f);
                const auto u_color = directional->color * directional->intensity;
                program->SetUniform(u_name + ".Direction", Vector3(u_dir));
                program->SetUniform(u_name + ".Color", u_color);
                directional_idx++;
            }

            if (auto point = light->As<PointLight>()) {
                const auto u_name = fmt::format("u_PointLights[{}]", point_idx);
                const auto u_pos = camera->view_transform * Vector4(light->GetWorldPosition(), 1.0f);
                const auto u_color = point->color * point->intensity;
                program->SetUniform(u_name + ".Position", u_pos);
                program->SetUniform(u_name + ".Color", u_color);
                program->SetUniform(u_name + ".Distance", point->distance);
                program->SetUniform(u_name + ".Decay", point->decay);
                point_idx++;
            }
        }
    }

    program->SetUniform("u_AmbientLight", ambient_light);
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

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->UpdateTransformHierarchy();
    camera->UpdateViewTransform();

    RenderObjects(scene, scene, camera);

    // TODO: reset rendering states
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    curr_wireframe_mode_ = false;
    curr_backface_culling_mode = false;
}

}