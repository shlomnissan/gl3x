// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/core/window.hpp"

#include "core/window_impl.hpp"

namespace engine {

Window::Window(const Window::Parameters& params)
  : impl_(std::make_unique<Impl>(params)) {}

auto Window::Start(const std::function<void(const double)>& tick) const -> void {
    impl_->Start(tick);
}

auto Window::Width() const -> int { return impl_->BufferWidth(); }

auto Window::Height() const -> int { return impl_->BufferHeight(); }

auto Window::AspectRatio() const -> float {
  return static_cast<float>(impl_->BufferWidth()) /
         static_cast<float>(impl_->BufferHeight());
};

Window::~Window() = default;

}