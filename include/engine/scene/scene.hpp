// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/node.hpp"

#include "core/event_dispatcher.hpp"

#include <memory>

namespace engine {

/**
 * @brief Represents the scene's root node.
 */
class ENGINE_EXPORT Scene : public Node {
public:
    // @brief Initializes a scene object.
    Scene();

    /**
     * @brief Updates the scene and all of its children.
     *
     * @param delta The time in seconds since the last update.
     */
    auto Update(double delta) -> void override;

    /**
     * @brief Creates a new instance of the Scene class.
     *
     * @return A `std::shared_ptr<Scene>` pointing to the newly created Scene instance.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Scene>();
    }

private:
    /// @brief Event listener for handling keyboard input events.
    std::shared_ptr<EventListener> keyboard_input_listener_;

    /**
     * @brief Propagate the "update event" to game nodes within the scene.
     *
     * @param node The node to update.
     * @param delta The time in seconds since the last update.
     */
    auto ProcessUpdates(std::weak_ptr<Node> node, double delta) -> void;

    /**
     * @brief Add event listeners to manage game nodes within the scene.
     */
    auto AddEventListeners() -> void;
};

}