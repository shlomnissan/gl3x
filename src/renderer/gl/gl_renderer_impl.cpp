// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "renderer/gl/gl_renderer_impl.hpp"

namespace engine {

Renderer::Impl::Impl(const Renderer::Parameters& params)
  : width_(params.width), height_(params.height) {}

auto Renderer::Impl::Render(Scene* scene, Camera* camera) -> void {
    scene->UpdateTransforms();
    camera->UpdateTransforms();
}

}