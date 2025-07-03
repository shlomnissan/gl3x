/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/events/event.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

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

}