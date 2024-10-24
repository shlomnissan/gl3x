// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/node.hpp"

#include "core/event.hpp"

namespace engine {

/**
 * @brief Abstract base class for game nodes in the engine.
 *
 * This class extends the Node class and provides an interface for game-specific
 * functionality such as updating the node's state and handling events.
 */
class ENGINE_EXPORT GameNode : public Node {
public:
    /**
     * @brief Update the game node's state.
     *
     * This method should be overridden in derived classes to implement
     * the logic for updating the node's state based on the elapsed time.
     *
     * @param delta The time elapsed since the last update, in seconds.
     */
    virtual auto Update(double delta) -> void = 0;

    /**
     * @brief Handle keyboard events for the game node.
     *
     * This method should be overridden in derived classes to implement
     * the logic for responding to keyboard events.
     *
     * @param event Pointer to the KeyboardEvent containing the event data.
     */
    virtual auto OnKeyboardEvent(KeyboardEvent* event) -> void = 0;
};

}