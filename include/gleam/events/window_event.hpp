/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/events/event.hpp"
#include "gleam/math/vector2.hpp"

namespace gleam {

/**
 * @brief Event representing changes to window attributes.
 *
 * @note Window events are handled internally by the runtime.
 *
 * @ingroup EventsGroup
 */
struct GLEAM_EXPORT WindowEvent : public Event {
    /**
     * @brief Represents window event types.
     * @ingroup EventsGroup
     */
    enum class Type {
        FramebufferSize,
    };

    /// @brief Window event type.
    WindowEvent::Type type;

    /// @brief Framebuffer size in physical pixels.
    Vector2 framebuffer;

    /**
     * @brief Returns event type.
     *
     * @return EventType::Window
     */
    auto GetType() const -> EventType override {
        return EventType::Window;
    }
};

}