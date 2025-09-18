/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/core/window.hpp"

#include "core/window_impl.hpp"

namespace gleam {

Window::Window(const Window::Parameters& params)
  : impl_(std::make_unique<Impl>(params)) {}

auto Window::Initialize() -> std::expected<void, std::string> {
    return impl_->Initialize();
}

auto Window::Start(const OnTickCallback& tick) const -> void {
    impl_->Start(tick);
}

auto Window::Break() -> void {
    impl_->Break();
}

auto Window::FramebufferWidth() const -> int {
    return impl_->framebuffer_width;
}

auto Window::FramebufferHeight() const -> int {
    return impl_->framebuffer_height;
}

auto Window::Width() const -> int {
    return impl_->window_width;
}

auto Window::Height() const -> int {
    return impl_->window_height;
}

auto Window::AspectRatio() const -> float {
  return static_cast<float>(impl_->window_width) /
         static_cast<float>(impl_->window_height);
};

auto Window::SetTitle(std::string_view title) -> void {
    impl_->SetTitle(title);
}

Window::~Window() = default;

}