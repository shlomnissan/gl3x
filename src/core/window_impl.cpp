// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "core/window_impl.hpp"

#include "engine/core/logger.hpp"

#include "core/event_dispatcher.hpp"

#include <memory>
#include <string>

namespace engine {

static auto glfw_get_error() -> std::string;
static auto glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods) -> void;
static auto glfw_cursor_pos_callback(GLFWwindow*, double x, double y) -> void;
static auto glfw_keyboard_map(int key) -> engine::Key;

Window::Impl::Impl(const Window::Parameters& params) {
    if (!glfwInit()) {
        Logger::Log(LogLevel::Error, "Failed to initialize GLFW {}", glfw_get_error());
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

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
        Logger::Log(LogLevel::Error, "Failed to create a GLFW window {}", glfw_get_error());
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
    glfwSetWindowUserPointer(window_, this);
    glfwGetFramebufferSize(window_, &buffer_width_, &buffer_height_);

    glfwSetKeyCallback(window_, glfw_key_callback);
    glfwSetCursorPosCallback(window_, glfw_cursor_pos_callback);
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
    Logger::Log(LogLevel::Info, "Vendor: {}", glGetString(GL_VENDOR));
    Logger::Log(LogLevel::Info, "Renderer: {}", glGetString(GL_RENDERER));
    Logger::Log(LogLevel::Info, "Version: {}", glGetString(GL_VERSION));
    Logger::Log(LogLevel::Info, "GLSL Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

Window::Impl::~Impl() {
    if (window_) glfwDestroyWindow(window_);
    if (initialized_) glfwTerminate();
}

static auto glfw_get_error() -> std::string {
    static const char* error_description;
    glfwGetError(&error_description);
    return error_description;
}

static auto glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods) -> void {
    auto event = std::make_unique<KeyboardEvent>(
        KeyboardEvent::Type::Pressed,
        glfw_keyboard_map(key)
    );

    if (action == GLFW_PRESS) {
        EventDispatcher::Get().Dispatch("keyboard_event", std::move(event));
    }

    if (action == GLFW_RELEASE) {
        event->type = KeyboardEvent::Type::Released;
        EventDispatcher::Get().Dispatch("keyboard_event", std::move(event));
    }
}

static auto glfw_cursor_pos_callback(GLFWwindow*, double x, double y) -> void {
    EventDispatcher::Get().Dispatch(
        "mouse_event",
        std::make_unique<MouseEvent>(
            MouseEvent::Type::Moved,
            x, y
        )
    );
}

auto glfw_keyboard_map(int key) -> engine::Key {
    switch(key) {
        case GLFW_KEY_SPACE: return engine::Key::Space;
        case GLFW_KEY_APOSTROPHE: return engine::Key::Apostrophe;
        case GLFW_KEY_COMMA: return engine::Key::Comma;
        case GLFW_KEY_MINUS: return engine::Key::Minus;
        case GLFW_KEY_PERIOD: return engine::Key::Period;
        case GLFW_KEY_SLASH: return engine::Key::Slash;
        case GLFW_KEY_0: return engine::Key::Key0;
        case GLFW_KEY_1: return engine::Key::Key1;
        case GLFW_KEY_2: return engine::Key::Key2;
        case GLFW_KEY_3: return engine::Key::Key3;
        case GLFW_KEY_4: return engine::Key::Key4;
        case GLFW_KEY_5: return engine::Key::Key5;
        case GLFW_KEY_6: return engine::Key::Key6;
        case GLFW_KEY_7: return engine::Key::Key7;
        case GLFW_KEY_8: return engine::Key::Key8;
        case GLFW_KEY_9: return engine::Key::Key9;
        case GLFW_KEY_SEMICOLON: return engine::Key::Semicolon;
        case GLFW_KEY_EQUAL: return engine::Key::Equal;
        case GLFW_KEY_A: return engine::Key::A;
        case GLFW_KEY_B: return engine::Key::B;
        case GLFW_KEY_C: return engine::Key::C;
        case GLFW_KEY_D: return engine::Key::D;
        case GLFW_KEY_E: return engine::Key::E;
        case GLFW_KEY_F: return engine::Key::F;
        case GLFW_KEY_G: return engine::Key::G;
        case GLFW_KEY_H: return engine::Key::H;
        case GLFW_KEY_I: return engine::Key::I;
        case GLFW_KEY_J: return engine::Key::J;
        case GLFW_KEY_K: return engine::Key::K;
        case GLFW_KEY_L: return engine::Key::L;
        case GLFW_KEY_M: return engine::Key::M;
        case GLFW_KEY_N: return engine::Key::N;
        case GLFW_KEY_O: return engine::Key::O;
        case GLFW_KEY_P: return engine::Key::P;
        case GLFW_KEY_Q: return engine::Key::Q;
        case GLFW_KEY_R: return engine::Key::R;
        case GLFW_KEY_S: return engine::Key::S;
        case GLFW_KEY_T: return engine::Key::T;
        case GLFW_KEY_U: return engine::Key::U;
        case GLFW_KEY_V: return engine::Key::V;
        case GLFW_KEY_W: return engine::Key::W;
        case GLFW_KEY_X: return engine::Key::X;
        case GLFW_KEY_Y: return engine::Key::Y;
        case GLFW_KEY_Z: return engine::Key::Z;
        case GLFW_KEY_LEFT_BRACKET: return engine::Key::LeftBracket;
        case GLFW_KEY_BACKSLASH: return engine::Key::Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return engine::Key::RightBracket;
        case GLFW_KEY_GRAVE_ACCENT: return engine::Key::GraveAccent;
        case GLFW_KEY_WORLD_1: return engine::Key::World1;
        case GLFW_KEY_WORLD_2: return engine::Key::World2;
        case GLFW_KEY_ESCAPE: return engine::Key::Escape;
        case GLFW_KEY_ENTER: return engine::Key::Enter;
        case GLFW_KEY_TAB: return engine::Key::Tab;
        case GLFW_KEY_BACKSPACE: return engine::Key::Backspace;
        case GLFW_KEY_INSERT: return engine::Key::Insert;
        case GLFW_KEY_DELETE: return engine::Key::Delete;
        case GLFW_KEY_RIGHT: return engine::Key::Right;
        case GLFW_KEY_LEFT: return engine::Key::Left;
        case GLFW_KEY_DOWN: return engine::Key::Down;
        case GLFW_KEY_UP: return engine::Key::Up;
        case GLFW_KEY_PAGE_UP: return engine::Key::PageUp;
        case GLFW_KEY_PAGE_DOWN: return engine::Key::PageDown;
        case GLFW_KEY_HOME: return engine::Key::Home;
        case GLFW_KEY_END: return engine::Key::End;
        case GLFW_KEY_CAPS_LOCK: return engine::Key::CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return engine::Key::ScrollLock;
        case GLFW_KEY_NUM_LOCK: return engine::Key::NumLock;
        case GLFW_KEY_PRINT_SCREEN: return engine::Key::PrintScreen;
        case GLFW_KEY_PAUSE: return engine::Key::Pause;
        case GLFW_KEY_F1: return engine::Key::F1;
        case GLFW_KEY_F2: return engine::Key::F2;
        case GLFW_KEY_F3: return engine::Key::F3;
        case GLFW_KEY_F4: return engine::Key::F4;
        case GLFW_KEY_F5: return engine::Key::F5;
        case GLFW_KEY_F6: return engine::Key::F6;
        case GLFW_KEY_F7: return engine::Key::F7;
        case GLFW_KEY_F8: return engine::Key::F8;
        case GLFW_KEY_F9: return engine::Key::F9;
        case GLFW_KEY_F10: return engine::Key::F10;
        case GLFW_KEY_F11: return engine::Key::F11;
        case GLFW_KEY_F12: return engine::Key::F12;
        case GLFW_KEY_F13: return engine::Key::F13;
        case GLFW_KEY_F14: return engine::Key::F14;
        case GLFW_KEY_F15: return engine::Key::F15;
        case GLFW_KEY_F16: return engine::Key::F16;
        case GLFW_KEY_F17: return engine::Key::F17;
        case GLFW_KEY_F18: return engine::Key::F18;
        case GLFW_KEY_F19: return engine::Key::F19;
        case GLFW_KEY_F20: return engine::Key::F20;
        case GLFW_KEY_F21: return engine::Key::F21;
        case GLFW_KEY_F22: return engine::Key::F22;
        case GLFW_KEY_F23: return engine::Key::F23;
        case GLFW_KEY_F24: return engine::Key::F24;
        case GLFW_KEY_F25: return engine::Key::F25;
        case GLFW_KEY_KP_0: return engine::Key::Keypad0;
        case GLFW_KEY_KP_1: return engine::Key::Keypad1;
        case GLFW_KEY_KP_2: return engine::Key::Keypad2;
        case GLFW_KEY_KP_3: return engine::Key::Keypad3;
        case GLFW_KEY_KP_4: return engine::Key::Keypad4;
        case GLFW_KEY_KP_5: return engine::Key::Keypad5;
        case GLFW_KEY_KP_6: return engine::Key::Keypad6;
        case GLFW_KEY_KP_7: return engine::Key::Keypad7;
        case GLFW_KEY_KP_8: return engine::Key::Keypad8;
        case GLFW_KEY_KP_9: return engine::Key::Keypad9;
        case GLFW_KEY_KP_DECIMAL: return engine::Key::KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE: return engine::Key::KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY: return engine::Key::KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return engine::Key::KeypadSubtract;
        case GLFW_KEY_KP_ADD: return engine::Key::KeypadAdd;
        case GLFW_KEY_KP_ENTER: return engine::Key::KeypadEnter;
        case GLFW_KEY_KP_EQUAL: return engine::Key::KeypadEqual;
        case GLFW_KEY_LEFT_SHIFT: return engine::Key::LeftShift;
        case GLFW_KEY_LEFT_CONTROL: return engine::Key::LeftControl;
        case GLFW_KEY_LEFT_ALT: return engine::Key::LeftAlt;
        case GLFW_KEY_LEFT_SUPER: return engine::Key::LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT: return engine::Key::RightShift;
        case GLFW_KEY_RIGHT_CONTROL: return engine::Key::RightControl;
        case GLFW_KEY_RIGHT_ALT: return engine::Key::RightAlt;
        case GLFW_KEY_RIGHT_SUPER: return engine::Key::RightSuper;
        case GLFW_KEY_MENU: return engine::Key::Menu;
        default: Logger::Log(LogLevel::Error, "Unrecognized GLFW key {}", key);
    }
    return engine::Key::Unknown;
}

}