// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/scene.hpp"

#include "engine/scene/game_node.hpp"

#include "core/event.hpp"
#include "core/event_dispatcher.hpp"
#include "core/logger.hpp"

#include <vector>

namespace engine {

Scene::Scene() {
    // When adding a game node to the scene, store it in a quick-access
    // ordered-set based on the node's level. This allows for efficient
    // invocation of updates and events without traversing the entire graph.
    EventDispatcher::Get().AddEventListener("added_to_scene", [&](Event* e) {
        auto scene_event = e->As<SceneEvent>();
        if (scene_event->node->Is<GameNode>()) {
            game_nodes_.emplace(CreateGameNodeRef(scene_event->node));
        }
    });

    // When removing a game node from the scene, check if it's stored in the
    // quick-access ordered-set. If so, remove it.
    EventDispatcher::Get().AddEventListener("removed_from_scene", [&](Event* e) {
        auto scene_event = e->As<SceneEvent>();
        if (scene_event->node->Is<GameNode>()) {
            auto node = CreateGameNodeRef(scene_event->node);
            auto it = game_nodes_.find(node);
            if (it != end(game_nodes_)) game_nodes_.erase(node);
        }
    });
}

auto Scene::ProcessUpdates(double delta) -> void {
    auto to_remove = std::vector<GameNodeRef> {};
    for (auto& game_node : game_nodes_) {
        if (auto node = game_node.ptr.lock()) {
            node->As<GameNode>()->Update(delta);
        } else {
            to_remove.emplace_back(game_node);
        }
    }
    for (auto& node : to_remove) game_nodes_.erase(node);
}

auto Scene::CreateGameNodeRef(std::shared_ptr<Node> game_node) const -> GameNodeRef {
    return GameNodeRef {
        .uuid = game_node->UUID(),
        .ptr = game_node,
        .level = game_node->level
    };
}

}