// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_renderer_impl.hpp"

#include "engine/core/logger.hpp"

#include "core/program_attributes.hpp"
#include "engine/materials/materials.hpp"

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
            if (curr_backface_culling != material->cull_backfaces) {
                material->cull_backfaces ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
                curr_backface_culling = material->cull_backfaces;
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

            if (attrs.lights) {
                // TODO: process lights
            }

            buffers_.Bind(geometry);

            SetUniforms(program, attrs, mesh, camera);

            program->Use();
            program->UpdateUniforms();

            auto primitive = GL_TRIANGLES;
            if (geometry->primitive == GeometryPrimitiveType::Lines) {
                primitive = GL_LINES;
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

auto Renderer::Impl::SetUniforms(GLProgram* program, const ProgramAttributes& attrs, Mesh* mesh, const Camera* camera) -> void {
    auto material = mesh->GetMaterial();
    auto model_view = camera->GetViewMatrix() * mesh->GetWorldTransform();

    program->SetUniform("u_Projection", camera->GetProjectionMatrix());
    program->SetUniform("u_ModelView", model_view);

    if (attrs.type == MaterialType::kFlatMaterial) {
        auto m = material->As<FlatMaterial>();
        program->SetUniform("u_AttribColor", m->color);
        if (attrs.texture_map) {
            program->SetUniform("u_AttribTextureMap", 0);
            textures_.Bind(m->texture_map.get());
        }
    }

    if (attrs.type == MaterialType::kPhongMaterial) {
        auto m = material->As<PhongMaterial>();
        program->SetUniform("u_AttribColor", m->color);
        program->SetUniform("u_NormalMatrix", Transpose(Inverse(Matrix3(model_view))));
        if (attrs.texture_map) {
            program->SetUniform("u_AttribTextureMap", 0);
            textures_.Bind(m->texture_map.get());
        }
    }
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

    scene->UpdateTransforms();
    camera->UpdateTransforms();

    RenderObjects(scene, scene, camera);
}

}