/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "core/window_impl.hpp"

#include "gleam/events/keyboard_event.hpp"
#include "gleam/events/mouse_event.hpp"
#include "gleam/events/window_event.hpp"

#include "events/event_dispatcher.hpp"
#include "utilities/logger.hpp"

#include <memory>
#include <string>

#ifdef GLEAM_USE_IMGUI
#include "core/imgui_integration.hpp"
#endif

namespace gleam {

static auto glfw_get_error() -> std::string;
static auto glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods) -> void;
static auto glfw_cursor_pos_callback(GLFWwindow*, double x, double y) -> void;
static auto glfw_mouse_button_callback(GLFWwindow*, int button, int action, int mods) -> void;
static auto glfw_scroll_callback(GLFWwindow*, double x, double y) -> void;
static auto glfw_mouse_button_map(int button) -> MouseButton;
static auto glfw_keyboard_map(int key) -> Key;
static auto glfw_framebuffer_size_callback(GLFWwindow*, int w, int h) -> void;
static auto glfw_window_size_callback(GLFWwindow*, int w, int h) -> void;
static auto glfw_content_scale_callback(GLFWwindow*, float sx, float sy) -> void;

Window::Impl::Impl(const Window::Parameters& params) {
    if (!glfwInit()) {
        Logger::Log(LogLevel::Error, "Failed to initialize GLFW {}", glfw_get_error());
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_SAMPLES, params.antialiasing);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    #endif

    window_ = glfwCreateWindow(params.width, params.height, "Untitled", nullptr, nullptr);

    if (window_ == nullptr) {
        Logger::Log(LogLevel::Error, "Failed to create a GLFW window {}", glfw_get_error());
        return;
    }

    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::Log(LogLevel::Error, "Failed to initialize GLAD OpenGL loader");
        return;
    }

    LogContextInfo();
    initialized_ = true;

    glfwSwapInterval(params.vsync ? 1 : 0);
    glfwSetWindowUserPointer(window_, this);
    glfwGetFramebufferSize(window_, &buffer_width, &buffer_height);
    glfwGetWindowSize(window_, &window_width, &window_height);
    glfwGetWindowContentScale(window_, &scale_x, &scale_y);

    glfwSetKeyCallback(window_, glfw_key_callback);
    glfwSetCursorPosCallback(window_, glfw_cursor_pos_callback);
    glfwSetMouseButtonCallback(window_, glfw_mouse_button_callback);
    glfwSetScrollCallback(window_, glfw_scroll_callback);
    glfwSetFramebufferSizeCallback(window_, glfw_framebuffer_size_callback);
    glfwSetWindowSizeCallback(window_, glfw_window_size_callback);
    glfwSetWindowContentScaleCallback(window_, glfw_content_scale_callback);

#ifdef GLEAM_USE_IMGUI
    imgui_initialize(window_);
#endif
}

auto Window::Impl::Start(const OnTickCallback& tick) -> void {
    while(!glfwWindowShouldClose(window_) && !break_) {
#ifdef GLEAM_USE_IMGUI
        imgui_begin_frame();
#endif

        tick();

#ifdef GLEAM_USE_IMGUI
        imgui_end_frame();
#endif

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

auto Window::Impl::Break() -> void {
    break_ = true;
}

auto Window::Impl::SetTitle(std::string_view title) -> void {
    glfwSetWindowTitle(window_, title.data());
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
#ifdef GLEAM_USE_IMGUI
    imgui_shutdown();
#endif

    if (window_) glfwDestroyWindow(window_);
    if (initialized_) glfwTerminate();
}

#pragma region GLFW callbacks

static auto glfw_get_error() -> std::string {
    static const char* error_description;
    glfwGetError(&error_description);
    return error_description;
}

static auto glfw_key_callback(GLFWwindow*, int key, int scancode, int action, int mods) -> void {
#ifdef GLEAM_USE_IMGUI
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

static auto glfw_cursor_pos_callback(GLFWwindow* window, double x, double y) -> void {
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

static auto glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int) -> void {
#ifdef GLEAM_USE_IMGUI
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

static auto glfw_scroll_callback(GLFWwindow* window, double x, double y) -> void {
#ifdef GLEAM_USE_IMGUI
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

static auto glfw_mouse_button_map(int button) -> MouseButton {
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        default: Logger::Log(LogLevel::Error, "Unrecognized GLFW mouse button key {}", button);
    }
    return MouseButton::None;
}

static auto prepare_window_event(GLFWwindow* window, WindowEvent* e) {
    int w = 0; int h = 0;
    float sx = 0.0f; float sy = 0.0f;

    glfwGetFramebufferSize(window, &w, &h);
    e->framebuffer = {static_cast<float>(w), static_cast<float>(h)};

    glfwGetWindowSize(window, &w, &h);
    e->window = {static_cast<float>(w), static_cast<float>(h)};

    glfwGetWindowContentScale(window, &sx, &sy);
    e->scale = {sx, sy};
}

static auto glfw_framebuffer_size_callback(GLFWwindow* window, int w, int h) -> void {
    auto instance = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));
    auto event = std::make_unique<WindowEvent>();
    event->type = WindowEvent::Type::FramebufferResize;

    instance->buffer_width = w;
    instance->buffer_height = h;

    prepare_window_event(window, event.get());

    EventDispatcher::Get().Dispatch("window_event", std::move(event));
}

static auto glfw_window_size_callback(GLFWwindow* window, int w, int h) -> void {
    auto instance = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));
    auto event = std::make_unique<WindowEvent>();
    event->type = WindowEvent::Type::WindowResize;

    instance->window_width = w;
    instance->window_height = h;

    prepare_window_event(window, event.get());

    EventDispatcher::Get().Dispatch("window_event", std::move(event));
}

static auto glfw_content_scale_callback(GLFWwindow* window, float sx, float sy) -> void {
    auto instance = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window));
    auto event = std::make_unique<WindowEvent>();
    event->type = WindowEvent::Type::ContentScale;

    instance->scale_x = sx;
    instance->scale_y = sy;

    prepare_window_event(window, event.get());

    EventDispatcher::Get().Dispatch("window_event", std::move(event));
}


static auto glfw_keyboard_map(int key) -> gleam::Key {
    switch(key) {
        case GLFW_KEY_SPACE: return gleam::Key::Space;
        case GLFW_KEY_APOSTROPHE: return gleam::Key::Apostrophe;
        case GLFW_KEY_COMMA: return gleam::Key::Comma;
        case GLFW_KEY_MINUS: return gleam::Key::Minus;
        case GLFW_KEY_PERIOD: return gleam::Key::Period;
        case GLFW_KEY_SLASH: return gleam::Key::Slash;
        case GLFW_KEY_0: return gleam::Key::Key0;
        case GLFW_KEY_1: return gleam::Key::Key1;
        case GLFW_KEY_2: return gleam::Key::Key2;
        case GLFW_KEY_3: return gleam::Key::Key3;
        case GLFW_KEY_4: return gleam::Key::Key4;
        case GLFW_KEY_5: return gleam::Key::Key5;
        case GLFW_KEY_6: return gleam::Key::Key6;
        case GLFW_KEY_7: return gleam::Key::Key7;
        case GLFW_KEY_8: return gleam::Key::Key8;
        case GLFW_KEY_9: return gleam::Key::Key9;
        case GLFW_KEY_SEMICOLON: return gleam::Key::Semicolon;
        case GLFW_KEY_EQUAL: return gleam::Key::Equal;
        case GLFW_KEY_A: return gleam::Key::A;
        case GLFW_KEY_B: return gleam::Key::B;
        case GLFW_KEY_C: return gleam::Key::C;
        case GLFW_KEY_D: return gleam::Key::D;
        case GLFW_KEY_E: return gleam::Key::E;
        case GLFW_KEY_F: return gleam::Key::F;
        case GLFW_KEY_G: return gleam::Key::G;
        case GLFW_KEY_H: return gleam::Key::H;
        case GLFW_KEY_I: return gleam::Key::I;
        case GLFW_KEY_J: return gleam::Key::J;
        case GLFW_KEY_K: return gleam::Key::K;
        case GLFW_KEY_L: return gleam::Key::L;
        case GLFW_KEY_M: return gleam::Key::M;
        case GLFW_KEY_N: return gleam::Key::N;
        case GLFW_KEY_O: return gleam::Key::O;
        case GLFW_KEY_P: return gleam::Key::P;
        case GLFW_KEY_Q: return gleam::Key::Q;
        case GLFW_KEY_R: return gleam::Key::R;
        case GLFW_KEY_S: return gleam::Key::S;
        case GLFW_KEY_T: return gleam::Key::T;
        case GLFW_KEY_U: return gleam::Key::U;
        case GLFW_KEY_V: return gleam::Key::V;
        case GLFW_KEY_W: return gleam::Key::W;
        case GLFW_KEY_X: return gleam::Key::X;
        case GLFW_KEY_Y: return gleam::Key::Y;
        case GLFW_KEY_Z: return gleam::Key::Z;
        case GLFW_KEY_LEFT_BRACKET: return gleam::Key::LeftBracket;
        case GLFW_KEY_BACKSLASH: return gleam::Key::Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return gleam::Key::RightBracket;
        case GLFW_KEY_GRAVE_ACCENT: return gleam::Key::GraveAccent;
        case GLFW_KEY_WORLD_1: return gleam::Key::World1;
        case GLFW_KEY_WORLD_2: return gleam::Key::World2;
        case GLFW_KEY_ESCAPE: return gleam::Key::Escape;
        case GLFW_KEY_ENTER: return gleam::Key::Enter;
        case GLFW_KEY_TAB: return gleam::Key::Tab;
        case GLFW_KEY_BACKSPACE: return gleam::Key::Backspace;
        case GLFW_KEY_INSERT: return gleam::Key::Insert;
        case GLFW_KEY_DELETE: return gleam::Key::Delete;
        case GLFW_KEY_RIGHT: return gleam::Key::Right;
        case GLFW_KEY_LEFT: return gleam::Key::Left;
        case GLFW_KEY_DOWN: return gleam::Key::Down;
        case GLFW_KEY_UP: return gleam::Key::Up;
        case GLFW_KEY_PAGE_UP: return gleam::Key::PageUp;
        case GLFW_KEY_PAGE_DOWN: return gleam::Key::PageDown;
        case GLFW_KEY_HOME: return gleam::Key::Home;
        case GLFW_KEY_END: return gleam::Key::End;
        case GLFW_KEY_CAPS_LOCK: return gleam::Key::CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return gleam::Key::ScrollLock;
        case GLFW_KEY_NUM_LOCK: return gleam::Key::NumLock;
        case GLFW_KEY_PRINT_SCREEN: return gleam::Key::PrintScreen;
        case GLFW_KEY_PAUSE: return gleam::Key::Pause;
        case GLFW_KEY_F1: return gleam::Key::F1;
        case GLFW_KEY_F2: return gleam::Key::F2;
        case GLFW_KEY_F3: return gleam::Key::F3;
        case GLFW_KEY_F4: return gleam::Key::F4;
        case GLFW_KEY_F5: return gleam::Key::F5;
        case GLFW_KEY_F6: return gleam::Key::F6;
        case GLFW_KEY_F7: return gleam::Key::F7;
        case GLFW_KEY_F8: return gleam::Key::F8;
        case GLFW_KEY_F9: return gleam::Key::F9;
        case GLFW_KEY_F10: return gleam::Key::F10;
        case GLFW_KEY_F11: return gleam::Key::F11;
        case GLFW_KEY_F12: return gleam::Key::F12;
        case GLFW_KEY_F13: return gleam::Key::F13;
        case GLFW_KEY_F14: return gleam::Key::F14;
        case GLFW_KEY_F15: return gleam::Key::F15;
        case GLFW_KEY_F16: return gleam::Key::F16;
        case GLFW_KEY_F17: return gleam::Key::F17;
        case GLFW_KEY_F18: return gleam::Key::F18;
        case GLFW_KEY_F19: return gleam::Key::F19;
        case GLFW_KEY_F20: return gleam::Key::F20;
        case GLFW_KEY_F21: return gleam::Key::F21;
        case GLFW_KEY_F22: return gleam::Key::F22;
        case GLFW_KEY_F23: return gleam::Key::F23;
        case GLFW_KEY_F24: return gleam::Key::F24;
        case GLFW_KEY_F25: return gleam::Key::F25;
        case GLFW_KEY_KP_0: return gleam::Key::Keypad0;
        case GLFW_KEY_KP_1: return gleam::Key::Keypad1;
        case GLFW_KEY_KP_2: return gleam::Key::Keypad2;
        case GLFW_KEY_KP_3: return gleam::Key::Keypad3;
        case GLFW_KEY_KP_4: return gleam::Key::Keypad4;
        case GLFW_KEY_KP_5: return gleam::Key::Keypad5;
        case GLFW_KEY_KP_6: return gleam::Key::Keypad6;
        case GLFW_KEY_KP_7: return gleam::Key::Keypad7;
        case GLFW_KEY_KP_8: return gleam::Key::Keypad8;
        case GLFW_KEY_KP_9: return gleam::Key::Keypad9;
        case GLFW_KEY_KP_DECIMAL: return gleam::Key::KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE: return gleam::Key::KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY: return gleam::Key::KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return gleam::Key::KeypadSubtract;
        case GLFW_KEY_KP_ADD: return gleam::Key::KeypadAdd;
        case GLFW_KEY_KP_ENTER: return gleam::Key::KeypadEnter;
        case GLFW_KEY_KP_EQUAL: return gleam::Key::KeypadEqual;
        case GLFW_KEY_LEFT_SHIFT: return gleam::Key::LeftShift;
        case GLFW_KEY_LEFT_CONTROL: return gleam::Key::LeftControl;
        case GLFW_KEY_LEFT_ALT: return gleam::Key::LeftAlt;
        case GLFW_KEY_LEFT_SUPER: return gleam::Key::LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT: return gleam::Key::RightShift;
        case GLFW_KEY_RIGHT_CONTROL: return gleam::Key::RightControl;
        case GLFW_KEY_RIGHT_ALT: return gleam::Key::RightAlt;
        case GLFW_KEY_RIGHT_SUPER: return gleam::Key::RightSuper;
        case GLFW_KEY_MENU: return gleam::Key::Menu;
        default: Logger::Log(LogLevel::Error, "Unrecognized GLFW key {}", key);
    }
    return gleam::Key::None;
}

#pragma endregion

}