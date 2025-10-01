/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/events/event.hpp"
#include "gleam/math/vector2.hpp"

namespace gleam {

enum class MouseButton;

/**
 * @brief Event representing mouse movement, clicks, or scroll input.
 *
 * `MouseEvent` is dispatched when the mouse moves, a button is pressed or
 * released, or the scroll wheel is used. Nodes can handle this event by
 * overriding the `OnMouseEvent()` method. The event contains mouse position,
 * scroll delta, button state, and event type.
 *
 * @code
 * class MyNode : public gleam::Node {
 * public:
 *   auto OnMouseEvent(gleam::MouseEvent* event) -> void override {
 *     if (
 *       event->type == gleam::MouseEvent::Type::ButtonPressed &&
 *       event->button == gleam::MouseButton::Left
 *     ) {
 *       Select();
 *     }
 *
 *     if (event->type == gleam::MouseEvent::Type::Moved) {
 *       UpdateCursor(event->position);
 *     }
 *   }
 * };
 * @endcode
 *
 * @ingroup EventsGroup
 */
struct GLEAM_EXPORT MouseEvent : public Event {
    /**
     * @brief Represents mouse interaction type.
     * @ingroup EventsGroup
     */
    enum class Type {
        Moved, ///< Cursor moved.
        ButtonPressed, ///< Button was pressed.
        ButtonReleased, ///< Button was released.
        Scrolled ///< Scroll wheel moved.
    };

    /// @brief Current cursor position in window coordinates.
    Vector2 position;

    /// @brief Scroll delta since last event.
    Vector2 scroll;

    /// @brief Mouse event type.
    MouseEvent::Type type;

    /// @brief Mouse button involved in the event (if any).
    MouseButton button;

    /**
     * @brief Returns event type.
     *
     * @return EventType::Mouse
     */
    auto GetType() const -> EventType override {
        return EventType::Mouse;
    }
};

/**
 * @brief Represents mouse buttons.
 * @ingroup EventsGroup
 */
enum class MouseButton {
    None,
    Left,
    Right,
    Middle
};

}