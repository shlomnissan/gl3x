/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/vector2.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>
#include <type_traits>

namespace gleam {

// Forward declarations
enum class Key;
enum class MouseButton;

enum class EventType {
    Keyboard,
    Mouse,
    Scene,
    Undefined
};

struct GLEAM_EXPORT Event {
    bool handled {false};

    [[nodiscard]] virtual auto GetType() const -> EventType { return EventType::Undefined; }

    virtual ~Event() = default;
};

struct GLEAM_EXPORT SceneEvent : public Event {
    enum class Type {
        NodeAdded,
        NodeRemoved
    };

    std::shared_ptr<Node> node;
    SceneEvent::Type type;

    SceneEvent(Type type, std::shared_ptr<Node> node) : type(type), node(node) {}

    auto GetType() const -> EventType override {
        return EventType::Scene;
    }
};

struct GLEAM_EXPORT KeyboardEvent : public Event {
    enum class Type {
        Pressed,
        Released
    };

    KeyboardEvent::Type type;
    Key key;

    auto GetType() const -> EventType override {
        return EventType::Keyboard;
    }
};

struct GLEAM_EXPORT MouseEvent : public Event {
    enum class Type {
        Moved,
        ButtonPressed,
        ButtonReleased,
        Scrolled
    };

    Vector2 position;
    Vector2 scroll;

    MouseEvent::Type type;
    MouseButton button;

    auto GetType() const -> EventType override {
        return EventType::Mouse;
    }
};

enum class MouseButton {
    None,
    Left,
    Right,
    Middle
};

enum class Key {
    None,
    Space,
    Apostrophe,
    Comma,
    Minus,
    Period,
    Slash,
    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    Semicolon,
    Equal,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LeftBracket,
    Backslash,
    RightBracket,
    GraveAccent,
    World1,
    World2,
    Escape,
    Enter,
    Tab,
    Backspace,
    Insert,
    Delete,
    Right,
    Left,
    Down,
    Up,
    PageUp,
    PageDown,
    Home,
    End,
    CapsLock,
    ScrollLock,
    NumLock,
    PrintScreen,
    Pause,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    Keypad0,
    Keypad1,
    Keypad2,
    Keypad3,
    Keypad4,
    Keypad5,
    Keypad6,
    Keypad7,
    Keypad8,
    Keypad9,
    KeypadDecimal,
    KeypadDivide,
    KeypadMultiply,
    KeypadSubtract,
    KeypadAdd,
    KeypadEnter,
    KeypadEqual,
    LeftShift,
    LeftControl,
    LeftAlt,
    LeftSuper,
    RightShift,
    RightControl,
    RightAlt,
    RightSuper,
    Menu,
};

}