/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "core/window.hpp"

#include <expected>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gleam {

class Window::Impl {
public:
    double mouse_pos_x {0.0};
    double mouse_pos_y {0.0};

    float scale_x {0.0f};
    float scale_y {0.0f};

    int framebuffer_width {0};
    int framebuffer_height {0};
    int window_width {0};
    int window_height {0};

    explicit Impl(const Window::Parameters& params);

    [[nodiscard]] auto Initialize() -> std::expected<void, std::string>;

    Impl(const Impl&) = delete;
    Impl(Impl&&) = delete;
    Impl& operator=(const Impl&) = delete;
    Impl& operator=(Impl&&) = delete;

    auto Start(const OnTickCallback& tick) -> void;

    auto Break() -> void;

    ~Impl();

private:
    Window::Parameters params_;

    GLFWwindow* window_ {nullptr};

    bool break_ {false};

    auto LogContextInfo() const -> void;
};

}