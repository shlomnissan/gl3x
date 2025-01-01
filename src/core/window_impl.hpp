// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/core/window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {

class Window::Impl {
public:
    double mouse_pos_x {0.0};
    double mouse_pos_y {0.0};

    explicit Impl(const Window::Parameters& params);

    Impl(const Impl&) = delete;
    Impl(Impl&&) = delete;
    Impl& operator=(const Impl&) = delete;
    Impl& operator=(Impl&&) = delete;

    auto Start(const OnTickCallback& tick) -> void;

    auto Break() -> void;

    auto SetTitle(std::string_view title) -> void;

    auto BufferWidth() const { return buffer_width_; }

    auto BufferHeight() const { return buffer_height_; }

    auto HasErrors() const { return !initialized_; }

    ~Impl();

private:
    int buffer_width_ {0};
    int buffer_height_ {0};

    bool initialized_ {false};
    bool break_ {false};

    GLFWwindow* window_ {nullptr};

    auto LogContextInfo() const -> void;
};

}