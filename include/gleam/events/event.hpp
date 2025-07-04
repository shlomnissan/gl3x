/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

namespace gleam {

/**
 * @brief Represents available event types.
 * @ingroup EventsGroup
 */
enum class EventType {
    Keyboard,
    Mouse,
    Scene,
    Undefined
};

/**
 * @internal
 * @brief Abstract base class for event types.
 *
 * Not intended for direct use.
 *
 * @ingroup EventsGroup
 */
struct GLEAM_EXPORT Event {
    bool handled {false};

    [[nodiscard]] virtual auto GetType() const -> EventType {
        return EventType::Undefined;
    }

    virtual ~Event() = default;
};

}