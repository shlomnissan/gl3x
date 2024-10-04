// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_renderer_impl.hpp"

#include "engine/scene/mesh.hpp"
#include "shaders/include/scene_frag.h"
#include "shaders/include/scene_vert.h"

#include <glad/glad.h>

namespace engine {

Renderer::Impl::Impl(const Renderer::Parameters& params)
  : params_(params),
    program_({
    {GLShaderType::kVertexShader, _SHADER_scene_vert},
    {GLShaderType::kFragmentShader, _SHADER_scene_frag}
}) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, params.width, params.height);

    program_.Use();
}

auto Renderer::Impl::RenderObject(Node* object, Camera* camera) -> void {
    for (const auto c : object->Children()) {
        if (c->Is<Mesh>()) {
            auto mesh = c->As<Mesh>();
            auto geometry = mesh->GetGeometry();
            auto material = mesh->GetMaterial();

            if (geometry->Disposed()) continue;

            program_.SetUniform(
                "ModelView",
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

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClearColor(
        params_.clear_color.r,
        params_.clear_color.g,
        params_.clear_color.b,
        params_.clear_color.a
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program_.SetUniform(
        "Projection",
        camera->GetProjectionMatrix()
    );

    scene->UpdateTransforms();
    camera->UpdateTransforms();

    RenderObject(scene, camera);
}

}