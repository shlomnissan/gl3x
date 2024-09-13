// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_renderer_impl.hpp"
#include "shaders/include/scene_vert.h"
#include "shaders/include/scene_frag.h"

#include <glad/glad.h>

namespace engine {

Renderer::Impl::Impl(const Renderer::Parameters& params) : program_ {{
    {GLShaderType::kVertexShader, _SHADER_scene_vert},
    {GLShaderType::kFragmentShader, _SHADER_scene_frag}
}} {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, params.width, params.height);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    program_.Use();
}

auto Renderer::Impl::RenderObject(Node* object, Camera* camera) -> void {
    for (const auto c : object->Children()) {
        if (c->Is<Mesh>()) {
            auto mesh = c->As<Mesh>();
            auto geometry = mesh->GetGeometry();

            if (geometry->Disposed()) return;

            program_.SetUniform(
                "ModelView",
                camera->GetViewMatrix() * c->GetWorldTransform()
            );

            bindings_.Bind(mesh);

            // TODO: draw triangles
            glDrawElements(
                GL_TRIANGLES,
                geometry->IndexData().size(),
                GL_UNSIGNED_INT,
                nullptr
            );
        }

        RenderObject(c.get(), camera);
    }
}

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
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