/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/events/event.hpp"
#include "vglx/nodes/node.hpp"

#include <memory>

namespace vglx {

/**
 * @brief Event representing a change in the scene graph hierarchy.
 *
 * `SceneEvent` is dispatched when a node is added to or removed from the
 * active scene. It contains a reference to the affected node and the type
 * of change.
 *
 * @note This event type is currently used internally by the active scene
 * object to track hierarchy changes and **cannot be handled by individual nodes**.
 *
 * @ingroup EventsGroup
 */
struct VGLX_EXPORT SceneEvent : public Event {
    /**
     * @brief Represents scene modification type.
     * @ingroup EventsGroup
     */
    enum class Type {
        NodeAdded, ///< Node was added to the scene.
        NodeRemoved ///< Node was removed from the scene.
    };

    /// @brief Node that was added or removed.
    std::shared_ptr<Node> node;

    /// @brief Scene event type.
    SceneEvent::Type type;

    /**
     * @brief Constructs a SceneEvent.
     *
     * @param type Type of scene change.
     * @param node Node that was affected.
     */
    SceneEvent(Type type, std::shared_ptr<Node> node) : type(type), node(node) {}

    /**
     * @brief Returns event type.
     *
     * @return EventType::Scene
     */
    auto GetType() const -> EventType override {
        return EventType::Scene;
    }
};

}