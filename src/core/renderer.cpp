// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/core/renderer.hpp"

#include "renderer/gl/gl_renderer_impl.hpp"

namespace engine {

Renderer::Renderer(const Renderer::Parameters& params)
    : impl_(std::make_unique<Impl>(params)) {}

auto Renderer::Render(Scene* scene, Camera* camera) -> void {
    impl_->Render(scene, camera);
}

auto Renderer::SetClearColor(const Color &color) -> void {
    impl_->SetClearColor(color);
}

auto Renderer::RenderedObjectsPerFrame() const -> size_t {
    return impl_->RenderedObjectsPerFrame();
}

Renderer::~Renderer() = default;

}