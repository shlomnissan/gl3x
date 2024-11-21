// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/node.hpp"

#include "core/event_dispatcher.hpp"
#include "lights/light.hpp"

#include <memory>
#include <vector>

namespace engine {

/**
 * @brief Represents the scene's root node.
 */
class ENGINE_EXPORT Scene : public Node, public std::enable_shared_from_this<Scene> {
public:
    // @brief Initializes a scene object.
    Scene();

    /**
     * @brief Updates the scene and all of its children.
     *
     * @param delta The time in seconds since the last update.
     */
    auto ProcessUpdates(float delta) -> void;

    /**
     * @brief Creates a new instance of the Scene class.
     *
     * @return A `std::shared_ptr<Scene>` pointing to the newly created Scene instance.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Scene>();
    }

private:
    /// @brief Event listener for handling input events.
    std::shared_ptr<EventListener> input_event_listener_;

    /// @brief Event listener for handling scene events.
    std::shared_ptr<EventListener> scene_event_listener_;

    /**
     * @brief A vector of weak pointers to lights in the scene.
     *
     * This vector stores weak pointers to `Light` objects that are part of the scene.
     * Storing light pointers in the scene object allows for quick access to light nodes.
     */
    std::vector<std::weak_ptr<Light>> lights_;

    /**
     * @brief Add event listeners to manage game nodes within the scene.
     */
    auto AddEventListeners() -> void;

    /**
     * @brief Propagate the "update event" to game nodes within the scene.
     *
     * @param node The node to update.
     * @param delta The time in seconds since the last update.
     */
    auto HandleNodeUpdates(std::weak_ptr<Node> node, float delta) -> void;

    /**
     * @brief Propagate input events to nodes within the scene.
     *
     * @param node The node to update.
     * @param event The input event to handle.
     */
    auto HandleInputEvent(std::weak_ptr<Node> node, Event* event) -> void;

    /**
     * @brief Handles events related to the scene.
     *
     * @param event The scene event to handle.
     */
    auto HandleSceneEvents(SceneEvent* event) -> void;

    /**
     * @brief Adds a light to the scene.
     *
     * @param light A shared pointer to the light to be added.
     */
    auto AddLight(std::shared_ptr<Light> light) -> void;

    /**
     * @brief Removes a light from the scene.
     *
     * @param light A shared pointer to the light to be removed.
    */
    auto RemoveLight(std::shared_ptr<Light> light) -> void;
};

}