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

enum class MouseButton;

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

}