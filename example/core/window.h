// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <functional>
#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/core/timer.hpp>

using ResizeCallback = std::function<void(const int, const int)>;

class Window {
public:
    Window(int width, int height, std::string_view title);

    auto Start(const std::function<void(const double delta)>& program) -> void;

    auto on_resize(ResizeCallback callback) { on_resize_ = callback; }
    auto on_resize() { return on_resize_; }

    ~Window();

private:
    GLFWwindow* window_ {nullptr};
    engine::Timer timer_ {};

    ResizeCallback on_resize_;
};