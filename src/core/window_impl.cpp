// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window_impl.hpp"

#include "core/logger.hpp"

#include <fmt/format.h>

namespace engine {

Window::Impl::Impl(const Window::Parameters& params) {
    if (!glfwInit()) return;

    initialized_ = true;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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
    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
        return;
    }

    LogContextInfo();
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

auto Window::Impl::LogContextInfo() const -> void {
    const GLubyte* version = glGetString(GL_VERSION);
    Logger::Log(LogLevel::Info, fmt::format("{} initialized", version));
}

Window::Impl::~Impl() {
    if (window_) glfwDestroyWindow(window_);
    if (initialized_) glfwTerminate();
}

}