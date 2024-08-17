// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>

namespace engine {

Window::Window(std::string_view title) : title_(title) {}

Window::Window(std::string_view title, int width, int height)
    : width_(width), height_(height), title_(title) {}

auto Window::Tick(const std::function<void (const double)> &tick) -> void {
    // TODO: impl
}

}