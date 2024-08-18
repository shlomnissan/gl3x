// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>
#include <engine/core/timer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine {

#pragma region implementation

class Window::Impl {
public:
    Impl() = default;

    // Delete the copy constructor and copy assignment operator
    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;

    // Delete the move constructor and move assignment operator
    Impl(Impl&&) = delete;
    Impl& operator=(Impl&&) = delete;

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

    template <typename T>
    auto Start(T&& tick) -> void {
        timer_.Start();
        while(!glfwWindowShouldClose(window_)) {
            auto delta = timer_.GetElapsedSeconds();
            timer_.Reset();

            tick(delta);

            glfwSwapBuffers(window_);
            glfwPollEvents();
        }
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

    Timer timer_ {};

    GLFWwindow* window_ {nullptr};
};

#pragma endregion

#pragma region delegate

Window::Window(std::string_view title, int width, int height)
  : impl_(std::make_unique<Impl>())
{
    impl_->Initialize(width, height, title);
}

auto Window::Start(const std::function<void(const double)>& tick) const -> void {
    impl_->Start(tick);
}

auto Window::width() const -> int { return impl_->BufferWidth(); }

auto Window::height() const -> int { return impl_->BufferHeight(); }

Window::~Window() = default;

#pragma endregion

}