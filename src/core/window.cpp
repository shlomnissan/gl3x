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

auto Window::Start(const OnTickCallback& tick) const -> void {
    impl_->Start(tick);
}

auto Window::Break() -> void {
    impl_->Break();
}

auto Window::SetTitle(std::string_view title) -> void {
    impl_->SetTitle(title);
}

auto Window::Width() const -> int {
    return impl_->BufferWidth();
}

auto Window::Height() const -> int {
    return impl_->BufferHeight();
}

auto Window::AspectRatio() const -> float {
  return static_cast<float>(impl_->BufferWidth()) /
         static_cast<float>(impl_->BufferHeight());
};

auto Window::HasErrors() const -> bool {
    return impl_->HasErrors();
}

Window::~Window() = default;

}