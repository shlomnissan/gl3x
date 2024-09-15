// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <engine/core/window.hpp>
#include <engine/core/timer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {

class Window::Impl {
public:
    explicit Impl(const Window::Parameters& params);

    Impl(const Impl&) = delete;
    Impl(Impl&&) = delete;
    Impl& operator=(const Impl&) = delete;
    Impl& operator=(Impl&&) = delete;

    auto Start(const std::function<void(const double)>& tick) -> void;

    auto BufferWidth() const { return buffer_width_; }

    auto BufferHeight() const { return buffer_height_; }

    ~Impl();

private:
    bool initialized_ {false};
    int buffer_width_ {0};
    int buffer_height_ {0};

    Timer timer_ {};

    GLFWwindow* window_ {nullptr};
};

}