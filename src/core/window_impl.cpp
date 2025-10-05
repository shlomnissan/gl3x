/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "core/window_impl.hpp"

#include "gl3x/events/keyboard_event.hpp"
#include "gl3x/events/mouse_event.hpp"

#include "events/event_dispatcher.hpp"
#include "utilities/logger.hpp"

#include <memory>
#include <string>

#ifdef GL3X_USE_IMGUI
#include "core/imgui_integration.hpp"
#endif

namespace gl3x {

namespace {

auto glfw_get_error() -> std::string;
auto glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods) -> void;
auto glfw_cursor_pos_callback(GLFWwindow*, double x, double y) -> void;
auto glfw_mouse_button_callback(GLFWwindow*, int button, int action, int mods) -> void;
auto glfw_scroll_callback(GLFWwindow*, double x, double y) -> void;
auto glfw_mouse_button_map(int button) -> MouseButton;
auto glfw_keyboard_map(int key) -> Key;
auto glfw_framebuffer_size_callback(GLFWwindow*, int w, int h) -> void;
auto glfw_window_size_callback(GLFWwindow*, int w, int h) -> void;

}

Window::Impl::Impl(const Window::Parameters& params) : params_(params) {}

auto Window::Impl::Initialize() -> std::expected<void, std::string> {
    if (!glfwInit()) {
        return std::unexpected("Failed to initialize GLFW " + glfw_get_error());
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_SAMPLES, params_.antialiasing);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    #endif

    window_ = glfwCreateWindow(
        params_.width,
        params_.height,
        params_.title.c_str(),
        nullptr,
        nullptr
    );

    if (window_ == nullptr) {
        return std::unexpected("Failed to create a GLFW window " + glfw_get_error());
    }

    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return std::unexpected("Failed to initialize GLAD OpenGL loader");
    }

    LogContextInfo();
    glfwSwapInterval(params_.vsync ? 1 : 0);
    glfwSetWindowUserPointer(window_, this);
    glfwGetFramebufferSize(window_, &framebuffer_width, &framebuffer_height);
    glfwGetWindowSize(window_, &window_width, &window_height);

    glfwSetKeyCallback(window_, glfw_key_callback);
    glfwSetCursorPosCallback(window_, glfw_cursor_pos_callback);
    glfwSetMouseButtonCallback(window_, glfw_mouse_button_callback);
    glfwSetScrollCallback(window_, glfw_scroll_callback);
    glfwSetFramebufferSizeCallback(window_, glfw_framebuffer_size_callback);
    glfwSetWindowSizeCallback(window_, glfw_window_size_callback);

#ifdef GL3X_USE_IMGUI
    imgui_initialize(window_);
#endif

    return {};
}

auto Window::Impl::PollEvents() -> void {
    glfwPollEvents();
    if (did_resize) {
        if (resize_callback_) {
            resize_callback_({
                framebuffer_width,
                framebuffer_height,
                window_width,
                window_height
            });
            did_resize = false;
        }
    }
}

auto Window::Impl::BeginUIFrame() -> void {
#ifdef GL3X_USE_IMGUI
    imgui_begin_frame();
#endif
}

auto Window::Impl::EndUIFrame() -> void {
#ifdef GL3X_USE_IMGUI
    imgui_end_frame();
#endif
}

auto Window::Impl::SwapBuffers() -> void {
    glfwSwapBuffers(window_);
}

auto Window::Impl::RequestClose() -> void {
    should_close_ = true;
}

auto Window::Impl::ShouldClose() -> bool {
    if (!should_close_) {
        should_close_ = glfwWindowShouldClose(window_);
    }
    return should_close_;
}

auto Window::Impl::SetTitle(std::string_view title) -> void {
    glfwSetWindowTitle(window_, title.data());
}

auto Window::Impl::SetResizeCallback(ResizeCallback callback) -> void {
    resize_callback_ = std::move(callback);
}

auto Window::Impl::LogContextInfo() const -> void {
    const auto getString = [](GLenum name) {
        return reinterpret_cast<const char*>(glGetString(name));
    };

    Logger::Log(LogLevel::Info, "Vendor: {}", getString(GL_VENDOR));
    Logger::Log(LogLevel::Info, "Renderer: {}", getString(GL_RENDERER));
    Logger::Log(LogLevel::Info, "Version: {}", getString(GL_VERSION));
    Logger::Log(LogLevel::Info, "GLSL Version: {}", getString(GL_SHADING_LANGUAGE_VERSION));
}

Window::Impl::~Impl() {
#ifdef GL3X_USE_IMGUI
    imgui_shutdown();
#endif

    if (window_) {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }
}

namespace {

auto glfw_get_error() -> std::string {
    static const char* error_description;
    glfwGetError(&error_description);
    return error_description;
}

auto glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods) -> void {
#ifdef GL3X_USE_IMGUI
    if (imgui_wants_input()) return;
#endif

    auto event = std::make_unique<KeyboardEvent>();
    event->type = KeyboardEvent::Type::Pressed;
    event->key = glfw_keyboard_map(key);

    if (action == GLFW_PRESS) {
        EventDispatcher::Get().Dispatch("keyboard_event", std::move(event));
    }

    if (action == GLFW_RELEASE) {
        event->type = KeyboardEvent::Type::Released;
        EventDispatcher::Get().Dispatch("keyboard_event", std::move(event));
    }
}

auto glfw_cursor_pos_callback(GLFWwindow* window, double x, double y) -> void {
    auto event = std::make_unique<MouseEvent>();
    auto instance = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));
    instance->mouse_pos_x = x;
    instance->mouse_pos_y = y;

    event->type = MouseEvent::Type::Moved;
    event->button = MouseButton::None;
    event->position = {static_cast<float>(x), static_cast<float>(y)};
    event->scroll = {0.0f, 0.0f};

    EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
}

auto glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int) -> void {
#ifdef GL3X_USE_IMGUI
    if (imgui_wants_input()) return;
#endif

    auto event = std::make_unique<MouseEvent>();
    auto instance = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));

    event->type = MouseEvent::Type::ButtonPressed;
    event->button = glfw_mouse_button_map(button);
    event->position = {
        static_cast<float>(instance->mouse_pos_x),
        static_cast<float>(instance->mouse_pos_y)
    };
    event->scroll = {0.0f, 0.0f};

    if (action == GLFW_PRESS) {
        EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
    }

    if (action == GLFW_RELEASE) {
        event->type = MouseEvent::Type::ButtonReleased;
        EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
    }
}

auto glfw_scroll_callback(GLFWwindow* window, double x, double y) -> void {
#ifdef GL3X_USE_IMGUI
    if (imgui_wants_input()) return;
#endif

    auto instance = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));
    auto event = std::make_unique<MouseEvent>();

    event->type = MouseEvent::Type::Scrolled;
    event->button = MouseButton::None;
    event->position = {
        static_cast<float>(instance->mouse_pos_x),
        static_cast<float>(instance->mouse_pos_y)
    };
    event->scroll = {static_cast<float>(x), static_cast<float>(y)};

    EventDispatcher::Get().Dispatch("mouse_event", std::move(event));
}

auto glfw_mouse_button_map(int button) -> MouseButton {
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        default: Logger::Log(LogLevel::Error, "Unrecognized GLFW mouse button key {}", button);
    }
    return MouseButton::None;
}

auto glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h) -> void {
    auto in = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));
    glfwGetFramebufferSize(window, &in->framebuffer_width, &in->framebuffer_height);
    in->did_resize = true;
}

auto glfw_window_size_callback(GLFWwindow* window, int w, int h) -> void {
    auto in = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));
    glfwGetWindowSize(window, &in->window_width, &in->window_height);
    in->did_resize = true;
}

auto glfw_keyboard_map(int key) -> gl3x::Key {
    switch(key) {
        case GLFW_KEY_SPACE: return gl3x::Key::Space;
        case GLFW_KEY_APOSTROPHE: return gl3x::Key::Apostrophe;
        case GLFW_KEY_COMMA: return gl3x::Key::Comma;
        case GLFW_KEY_MINUS: return gl3x::Key::Minus;
        case GLFW_KEY_PERIOD: return gl3x::Key::Period;
        case GLFW_KEY_SLASH: return gl3x::Key::Slash;
        case GLFW_KEY_0: return gl3x::Key::Key0;
        case GLFW_KEY_1: return gl3x::Key::Key1;
        case GLFW_KEY_2: return gl3x::Key::Key2;
        case GLFW_KEY_3: return gl3x::Key::Key3;
        case GLFW_KEY_4: return gl3x::Key::Key4;
        case GLFW_KEY_5: return gl3x::Key::Key5;
        case GLFW_KEY_6: return gl3x::Key::Key6;
        case GLFW_KEY_7: return gl3x::Key::Key7;
        case GLFW_KEY_8: return gl3x::Key::Key8;
        case GLFW_KEY_9: return gl3x::Key::Key9;
        case GLFW_KEY_SEMICOLON: return gl3x::Key::Semicolon;
        case GLFW_KEY_EQUAL: return gl3x::Key::Equal;
        case GLFW_KEY_A: return gl3x::Key::A;
        case GLFW_KEY_B: return gl3x::Key::B;
        case GLFW_KEY_C: return gl3x::Key::C;
        case GLFW_KEY_D: return gl3x::Key::D;
        case GLFW_KEY_E: return gl3x::Key::E;
        case GLFW_KEY_F: return gl3x::Key::F;
        case GLFW_KEY_G: return gl3x::Key::G;
        case GLFW_KEY_H: return gl3x::Key::H;
        case GLFW_KEY_I: return gl3x::Key::I;
        case GLFW_KEY_J: return gl3x::Key::J;
        case GLFW_KEY_K: return gl3x::Key::K;
        case GLFW_KEY_L: return gl3x::Key::L;
        case GLFW_KEY_M: return gl3x::Key::M;
        case GLFW_KEY_N: return gl3x::Key::N;
        case GLFW_KEY_O: return gl3x::Key::O;
        case GLFW_KEY_P: return gl3x::Key::P;
        case GLFW_KEY_Q: return gl3x::Key::Q;
        case GLFW_KEY_R: return gl3x::Key::R;
        case GLFW_KEY_S: return gl3x::Key::S;
        case GLFW_KEY_T: return gl3x::Key::T;
        case GLFW_KEY_U: return gl3x::Key::U;
        case GLFW_KEY_V: return gl3x::Key::V;
        case GLFW_KEY_W: return gl3x::Key::W;
        case GLFW_KEY_X: return gl3x::Key::X;
        case GLFW_KEY_Y: return gl3x::Key::Y;
        case GLFW_KEY_Z: return gl3x::Key::Z;
        case GLFW_KEY_LEFT_BRACKET: return gl3x::Key::LeftBracket;
        case GLFW_KEY_BACKSLASH: return gl3x::Key::Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return gl3x::Key::RightBracket;
        case GLFW_KEY_GRAVE_ACCENT: return gl3x::Key::GraveAccent;
        case GLFW_KEY_WORLD_1: return gl3x::Key::World1;
        case GLFW_KEY_WORLD_2: return gl3x::Key::World2;
        case GLFW_KEY_ESCAPE: return gl3x::Key::Escape;
        case GLFW_KEY_ENTER: return gl3x::Key::Enter;
        case GLFW_KEY_TAB: return gl3x::Key::Tab;
        case GLFW_KEY_BACKSPACE: return gl3x::Key::Backspace;
        case GLFW_KEY_INSERT: return gl3x::Key::Insert;
        case GLFW_KEY_DELETE: return gl3x::Key::Delete;
        case GLFW_KEY_RIGHT: return gl3x::Key::Right;
        case GLFW_KEY_LEFT: return gl3x::Key::Left;
        case GLFW_KEY_DOWN: return gl3x::Key::Down;
        case GLFW_KEY_UP: return gl3x::Key::Up;
        case GLFW_KEY_PAGE_UP: return gl3x::Key::PageUp;
        case GLFW_KEY_PAGE_DOWN: return gl3x::Key::PageDown;
        case GLFW_KEY_HOME: return gl3x::Key::Home;
        case GLFW_KEY_END: return gl3x::Key::End;
        case GLFW_KEY_CAPS_LOCK: return gl3x::Key::CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return gl3x::Key::ScrollLock;
        case GLFW_KEY_NUM_LOCK: return gl3x::Key::NumLock;
        case GLFW_KEY_PRINT_SCREEN: return gl3x::Key::PrintScreen;
        case GLFW_KEY_PAUSE: return gl3x::Key::Pause;
        case GLFW_KEY_F1: return gl3x::Key::F1;
        case GLFW_KEY_F2: return gl3x::Key::F2;
        case GLFW_KEY_F3: return gl3x::Key::F3;
        case GLFW_KEY_F4: return gl3x::Key::F4;
        case GLFW_KEY_F5: return gl3x::Key::F5;
        case GLFW_KEY_F6: return gl3x::Key::F6;
        case GLFW_KEY_F7: return gl3x::Key::F7;
        case GLFW_KEY_F8: return gl3x::Key::F8;
        case GLFW_KEY_F9: return gl3x::Key::F9;
        case GLFW_KEY_F10: return gl3x::Key::F10;
        case GLFW_KEY_F11: return gl3x::Key::F11;
        case GLFW_KEY_F12: return gl3x::Key::F12;
        case GLFW_KEY_F13: return gl3x::Key::F13;
        case GLFW_KEY_F14: return gl3x::Key::F14;
        case GLFW_KEY_F15: return gl3x::Key::F15;
        case GLFW_KEY_F16: return gl3x::Key::F16;
        case GLFW_KEY_F17: return gl3x::Key::F17;
        case GLFW_KEY_F18: return gl3x::Key::F18;
        case GLFW_KEY_F19: return gl3x::Key::F19;
        case GLFW_KEY_F20: return gl3x::Key::F20;
        case GLFW_KEY_F21: return gl3x::Key::F21;
        case GLFW_KEY_F22: return gl3x::Key::F22;
        case GLFW_KEY_F23: return gl3x::Key::F23;
        case GLFW_KEY_F24: return gl3x::Key::F24;
        case GLFW_KEY_F25: return gl3x::Key::F25;
        case GLFW_KEY_KP_0: return gl3x::Key::Keypad0;
        case GLFW_KEY_KP_1: return gl3x::Key::Keypad1;
        case GLFW_KEY_KP_2: return gl3x::Key::Keypad2;
        case GLFW_KEY_KP_3: return gl3x::Key::Keypad3;
        case GLFW_KEY_KP_4: return gl3x::Key::Keypad4;
        case GLFW_KEY_KP_5: return gl3x::Key::Keypad5;
        case GLFW_KEY_KP_6: return gl3x::Key::Keypad6;
        case GLFW_KEY_KP_7: return gl3x::Key::Keypad7;
        case GLFW_KEY_KP_8: return gl3x::Key::Keypad8;
        case GLFW_KEY_KP_9: return gl3x::Key::Keypad9;
        case GLFW_KEY_KP_DECIMAL: return gl3x::Key::KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE: return gl3x::Key::KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY: return gl3x::Key::KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return gl3x::Key::KeypadSubtract;
        case GLFW_KEY_KP_ADD: return gl3x::Key::KeypadAdd;
        case GLFW_KEY_KP_ENTER: return gl3x::Key::KeypadEnter;
        case GLFW_KEY_KP_EQUAL: return gl3x::Key::KeypadEqual;
        case GLFW_KEY_LEFT_SHIFT: return gl3x::Key::LeftShift;
        case GLFW_KEY_LEFT_CONTROL: return gl3x::Key::LeftControl;
        case GLFW_KEY_LEFT_ALT: return gl3x::Key::LeftAlt;
        case GLFW_KEY_LEFT_SUPER: return gl3x::Key::LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT: return gl3x::Key::RightShift;
        case GLFW_KEY_RIGHT_CONTROL: return gl3x::Key::RightControl;
        case GLFW_KEY_RIGHT_ALT: return gl3x::Key::RightAlt;
        case GLFW_KEY_RIGHT_SUPER: return gl3x::Key::RightSuper;
        case GLFW_KEY_MENU: return gl3x::Key::Menu;
        default: Logger::Log(LogLevel::Error, "Unrecognized GLFW key {}", key);
    }
    return gl3x::Key::None;
}

}

}