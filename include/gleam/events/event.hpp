/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

namespace gleam {

enum class EventType {
    Keyboard,
    Mouse,
    Scene,
    Undefined
};

struct GLEAM_EXPORT Event {
    bool handled {false};

    [[nodiscard]] virtual auto GetType() const -> EventType {
        return EventType::Undefined;
    }

    virtual ~Event() = default;
};

}