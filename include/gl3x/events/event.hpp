/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

namespace gl3x {

/**
 * @brief Represents available event types.
 * @ingroup EventsGroup
 */
enum class EventType {
    Keyboard,
    Mouse,
    Scene,
    Window,
    Undefined
};

/**
 * @brief Abstract base class for event types.
 *
 * Not intended for direct use.
 *
 * @ingroup EventsGroup
 */
struct GL3X_EXPORT Event {
    /**
     * @brief Indicates whether the event has been handled.
     *
     * When set to `true`, this flag prevents the event from propagating
     * further to other nodes in the scene graph. Handlers should set this
     * to `true` if no other node should respond to the event.
     *
     * @code
     * auto OnKeyboardEvent(gl3x::KeyboardEvent* event) -> void override {
     *   if (event->key == gl3x::Key::Escape) {
     *     QuitApplication();
     *     event->handled = true; // Stop further propagation
     *   }
     * }
     * @endcode
     */
    bool handled {false};

    /**
     * @brief Returns event type.
     *
     * @return EventType::Undefined
     */
    [[nodiscard]] virtual auto GetType() const -> EventType {
        return EventType::Undefined;
    }

    /**
     * @brief Destructor.
     */
    virtual ~Event() = default;
};

}