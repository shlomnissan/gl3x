// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_renderer_impl.hpp"

#include "core/logger.hpp"
#include "core/program_attributes.hpp"

#include <glad/glad.h>

namespace engine {

Renderer::Impl::Impl(const Renderer::Parameters& params) : params_(params) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, params.width, params.height);
}

auto Renderer::Impl::RenderObject(Node* object, Camera* camera) -> void {
    for (const auto c : object->Children()) {
        if (c->Is<Mesh>()) {
            auto mesh = c->As<Mesh>();
            auto geometry = mesh->GetGeometry();
            auto material = mesh->GetMaterial();

            if (!IsValidMesh(mesh)) continue;

            auto program_attribs = ProgramAttributes {material};
            auto program = programs_.GetProgram(mesh);
            program->Use();

            program->SetUniform("Projection",
                camera->GetProjectionMatrix()
            );

            program->SetUniform("ModelView",
                camera->GetViewMatrix() * c->GetWorldTransform()
            );

            buffers_.Bind(geometry);

            if (geometry->IndexData().empty()) {
                glDrawArrays(GL_TRIANGLES, 0, geometry->VertexCount());
            } else {
                glDrawElements(
                    GL_TRIANGLES,
                    geometry->IndexData().size(),
                    GL_UNSIGNED_INT,
                    nullptr
                );
            }
        }

        RenderObject(c.get(), camera);
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
    glClearColor(
        params_.clear_color.r,
        params_.clear_color.g,
        params_.clear_color.b,
        params_.clear_color.a
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->UpdateTransforms();
    camera->UpdateTransforms();

    RenderObject(scene, camera);
}

}