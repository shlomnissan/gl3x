/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/events/event.hpp"

namespace gleam {

enum class Key;

/**
 * @brief Event representing a keyboard key press or release.
 *
 * `KeyboardEvent` is dispatched when a key is pressed or released. Nodes can
 * handle this event by overriding the `OnKeyboardEvent()` method. The event
 * contains both the key involved and the type of interaction.
 *
 * @code
 * class MyNode : public gleam::Node {
 * public:
 *   auto OnKeyboardEvent(gleam::KeyboardEvent* event) -> void override {
 *     if (event->type == gleam::KeyboardEvent::Type::Pressed) {
 *       if (event->key == gleam::Key::Sapce) {
 *         Jump();
 *         event->handled = true; // stop propagation
 *       }
 *     }
 *   }
 * };
 * @endcode
 *
 * @ingroup EventsGroup
 */
struct GLEAM_EXPORT KeyboardEvent : public Event {
    /**
     * @brief Represents keyboard interaction type.
     * @ingroup EventsGroup
     */
    enum class Type {
        Pressed, ///< Key was pressed down.
        Released ///< Key was released.
    };

    /// @brief Keyboard event type.
    KeyboardEvent::Type type;

    /// @brief Key code associated with the event.
    Key key;

    /**
     * @brief Returns event type.
     *
     * @return EventType::Keyboard
     */
    auto GetType() const -> EventType override {
        return EventType::Keyboard;
    }
};

/**
 * @brief Represents keyboard keys.
 * @ingroup EventsGroup
 */
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