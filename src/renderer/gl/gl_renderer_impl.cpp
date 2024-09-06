// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_renderer_impl.hpp"

#include <glad/glad.h>

namespace engine {

Renderer::Impl::Impl(const Renderer::Parameters& params) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, params.width, params.height);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->UpdateTransforms();
    camera->UpdateTransforms();
}

}