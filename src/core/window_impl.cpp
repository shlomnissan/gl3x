// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window_impl.hpp"

namespace engine {

Window::Impl::Impl(const Window::Parameters& params) {
    if (!glfwInit()) return;

    initialized_ = true;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    #endif

    window_ = glfwCreateWindow(
        params.width,
        params.height,
        params.title.data(),
        nullptr,
        nullptr
    );

    if (window_ == nullptr) return;

    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glfwSwapInterval(1);
    glfwGetFramebufferSize(window_, &buffer_width_, &buffer_height_);
}

auto Window::Impl::Start(const std::function<void(const double)>& tick) -> void {
    timer_.Start();
    while(!glfwWindowShouldClose(window_)) {
        auto delta = timer_.GetElapsedSeconds();
        timer_.Reset();

        tick(delta);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

Window::Impl::~Impl() {
    if (window_) glfwDestroyWindow(window_);
    if (initialized_) glfwTerminate();
}

}