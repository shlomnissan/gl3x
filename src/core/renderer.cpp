/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/core/renderer.hpp"

#include "renderer/gl/gl_renderer_impl.hpp"

namespace gl3x {

Renderer::Renderer(const Renderer::Parameters& params)
    : impl_(std::make_unique<Impl>(params)) {}

auto Renderer::Initialize() -> std::expected<void, std::string> {
    return impl_->Initialize();
}

auto Renderer::Render(Scene* scene, Camera* camera) -> void {
    impl_->Render(scene, camera);
}

auto Renderer::SetViewport(int x, int y, int width, int height) -> void {
    impl_->SetViewport(x, y, width, height);
}

auto Renderer::SetClearColor(const Color& color) -> void {
    impl_->SetClearColor(color);
}

auto Renderer::RenderedObjectsPerFrame() const -> size_t {
    return impl_->RenderedObjectsPerFrame();
}

Renderer::~Renderer() = default;

}