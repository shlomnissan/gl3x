// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/window_impl.hpp"

#include "core/logger.hpp"

#include <string>

namespace engine {

static const char* error_description;
static auto GLFWGetError() -> std::string {
    glfwGetError(&error_description);
    return error_description;
}

Window::Impl::Impl(const Window::Parameters& params) {
    if (!glfwInit()) {
        Logger::Log(LogLevel::Error, "Failed to initialize GLFW {}", GLFWGetError());
        return;
    }

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

    if (window_ == nullptr) {
        Logger::Log(LogLevel::Error, "Failed to create a GLFW window {}", GLFWGetError());
        return;
    }

    glfwMakeContextCurrent(window_);
    if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
        Logger::Log(LogLevel::Error, "Failed to initialize GLAD using GLES2 loader");
        return;
    }

    LogContextInfo();
    initialized_ = true;

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

        // TODO: move to an event handler
        if (on_event_) { on_event_(); }
    }
}

auto Window::Impl::LogContextInfo() const -> void {
    Logger::Log(LogLevel::Info, "Vendor: {}", glGetString(GL_VENDOR));
    Logger::Log(LogLevel::Info, "Renderer: {}", glGetString(GL_RENDERER));
    Logger::Log(LogLevel::Info, "Version: {}", glGetString(GL_VERSION));
    Logger::Log(LogLevel::Info, "GLSL Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

Window::Impl::~Impl() {
    if (window_) {
        glfwDestroyWindow(window_);
    }
    if (initialized_) {
        glfwTerminate();
    }
}

}