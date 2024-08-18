// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window.h"

#include <GLFW/glfw3.h>
#include <fmt/format.h>

constexpr auto callback_error =
[](int error, const char* message) {
    fmt::print("Error ({}): {}\n", error, message);
};

constexpr auto callback_resize =
[](GLFWwindow *window, int width, int height) {
    auto buffer_width {0}, buffer_height {0};
    glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
    glViewport(0, 0, buffer_width, buffer_height);
    auto instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (instance->on_resize()) {
        instance->on_resize()(width, height);
    }
};

Window::Window(int width, int height, std::string_view title) {
    glfwSetErrorCallback(callback_error);

    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    #endif

    window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (window_ == nullptr) {
        glfwTerminate();
        return;
    }

     glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window_, callback_resize);
    glfwSetWindowUserPointer(window_, this);

    auto buffer_width {0}, buffer_height {0};
    glfwGetFramebufferSize(window_, &buffer_width, &buffer_height);
    glViewport(0, 0, buffer_width, buffer_height);
}

auto Window::Start(const std::function<void(const double delta)> &program) -> void {
    timer_.Reset();

    while(!glfwWindowShouldClose(window_)) {
        auto delta = timer_.GetElapsedSeconds();
        timer_.Reset();

        program(delta);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

Window::~Window() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}