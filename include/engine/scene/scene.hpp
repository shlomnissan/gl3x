// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/scene/node.hpp"
#include "engine/scene/game_node.hpp"

#include <memory>
#include <set>

namespace engine {

struct GameNodeRef;

/**
 * @brief Represents the scene's root node.
 */
class ENGINE_EXPORT Scene : public Node {
public:
    // @brief Initializes a scene object.
    Scene();

    /**
     * @brief Propagate the "update event" to game nodes within the scene.
     *
     * @param delta The time in seconds since the last update.
     */
    auto ProcessUpdates(double delta) -> void;

    /**
     * @brief Creates a new instance of the Scene class.
     *
     * @return A `std::shared_ptr<Scene>` pointing to the newly created Scene instance.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Scene>();
    }

private:
    /// @brief A set of game node references in the scene ordered by level.
    std::set<GameNodeRef> game_nodes_;

    /**
     * @brief Factory for game node references.
     *
     * @param game_node A `std::shared_ptr<Node>` pointing to the game node to reference.
     * @return A `GameNodeRef` containing the reference to the game node.
     */
    auto CreateGameNodeRef(std::shared_ptr<Node> game_node) const -> GameNodeRef;
};

/**
 * @brief Represents a reference to a game node in the scene.
 */
struct GameNodeRef {
    /// @brief The unique identifier of the game node.
    std::string uuid;
    /// @brief A weak pointer to the corresponding Node in the scene.
    std::weak_ptr<Node> ptr;
    /// @brief The level of the game node in the scene hierarchy.
    int level;

    /**
     * @brief Compares this game node reference with another for ordering.
     *
     * @param other The other game node reference to compare against.
     * @return True if this node's level is less than the other's level.
     */
    auto operator<(const GameNodeRef& other) const -> bool {
        if (level == other.level) {
            return uuid < other.uuid;
        }
        return level < other.level;
    }
};

}