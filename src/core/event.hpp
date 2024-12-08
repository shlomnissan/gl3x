// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/vector2.hpp"
#include "engine/nodes/node.hpp"

#include <memory>
#include <type_traits>

namespace engine {

struct Event {
    bool handled {false};

    template<class T> requires std::is_base_of_v<Event, T>
    [[nodiscard]] auto Is() const {
        return dynamic_cast<const T*>(this) != nullptr;
    }

    template<class T> requires std::is_base_of_v<Event, T>
    [[nodiscard]] auto As() {
        return dynamic_cast<T*>(this);
    }

    template<class T> requires std::is_base_of_v<Event, T>
    [[nodiscard]] auto As() const {
        return dynamic_cast<const T*>(this);
    }

    virtual ~Event() = default;
};

struct SceneEvent : public Event {
    enum class Type {
        AddedToScene,
        RemovedFromScene
    };

    std::shared_ptr<Node> node;
    SceneEvent::Type type;

    SceneEvent(Type type, std::shared_ptr<Node> node) : type(type), node(node) {}
};

enum class Key; ///< forward declaration

struct KeyboardEvent : public Event {
    enum class Type {
        Pressed,
        Released
    };

    KeyboardEvent::Type type;
    Key key;
};

enum class MouseButton; ///< forward declaration

struct MouseEvent : public Event {
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