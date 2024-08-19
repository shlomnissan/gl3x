// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>

#include "window_impl.hpp"

namespace engine {

Window::Window(const Window::Parameters& params)
  : impl_(std::make_unique<Impl>())
{
    impl_->Initialize(params);
}

auto Window::Start(const std::function<void(const double)>& tick) const -> void {
    impl_->Start(tick);
}

auto Window::width() const -> int { return impl_->BufferWidth(); }

auto Window::height() const -> int { return impl_->BufferHeight(); }

Window::~Window() = default;

}