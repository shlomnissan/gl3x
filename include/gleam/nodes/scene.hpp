/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/core/events.hpp"
#include "gleam/math/color.hpp"
#include "gleam/nodes/fog.hpp"
#include "gleam/nodes/node.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace gleam {

// Forward declarations
class Renderer;

using EventListener = std::function<void(Event*)>;

/**
 * @brief Represents the scene's root node.
 */
class GLEAM_EXPORT Scene : public Node {
public:
    /// @brief Unique pointer to a fog object for the scene.
    std::unique_ptr<Fog> fog;

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

    /**
     * @brief Returns node type.
     *
     * @return NodeType::SceneNode
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::SceneNode;
    }

    /**
     * @brief Destructor for the Scene class.
     */
    ~Scene() override;

private:
    /// @brief The renderer accesses the 'touched_' flag.
    friend class Renderer;

    /// @brief The application context invokes the scene's 'SetContext' method.
    friend class ApplicationContext;

    friend class ApplicationContext;

    /// @brief Event listener for handling input events.
    std::shared_ptr<EventListener> input_event_listener_;

    /// @brief Event listener for handling scene events.
    std::shared_ptr<EventListener> scene_event_listener_;

    /**
     * @brief Tracks whether a node was added to or removed from the scene.
     * This flag informs the renderer to update its internal render lists for
     * managing render order. The renderer accesses this flag directly via
     * the friend class declaration.
     */
    bool touched_ = false;

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
    auto HandleSceneEvents(const SceneEvent* event) -> void;

    /**
     * @brief Sets the shared context for the scene and its nodes.
     *
     * This method initializes the shared context for the scene and propagates it
     * to all nodes within the scene. The shared context provides access to shared
     * resources and parameters required by the scene and its nodes.
     *
     * @param context A pointer to the shared context to be set for the scene.
     */
    auto SetContext(SharedContext* context) -> void;
};

}