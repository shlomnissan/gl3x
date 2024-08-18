// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>

#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {

#pragma region implementation

class Window::Impl {
public:
    auto Initialize(int width, int height, std::string_view title) {
        if (!glfwInit()) return;

        initialized_ = true;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        if (window_ == nullptr) return;

        glfwMakeContextCurrent(window_);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            return;
        }

        glfwSwapInterval(1);
        glfwGetFramebufferSize(window_, &buffer_width_, &buffer_height_);
    }

    auto BufferWidth() const { return buffer_width_; }

    auto BufferHeight() const { return buffer_height_; }

    ~Impl() {
        if (window_) glfwDestroyWindow(window_);
        if (initialized_) glfwTerminate();
    }

private: 
    bool initialized_ {false};
    int buffer_width_ {0};
    int buffer_height_ {0};

    GLFWwindow* window_ {nullptr};
};

#pragma endregion

#pragma region delegate

Window::Window(std::string_view title, int width, int height)
  : impl_(std::make_unique<Impl>())
{
    impl_->Initialize(width, height, title);
}

auto Window::width() const -> int { return impl_->BufferWidth(); }

auto Window::height() const -> int { return impl_->BufferHeight(); }

#pragma endregion

}