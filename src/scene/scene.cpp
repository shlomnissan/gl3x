// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/scene.hpp"

#include "engine/scene/game_node.hpp"

#include "core/logger.hpp"

#include <vector>

namespace engine {

Scene::Scene() {
    AddEventListeners();
}

auto Scene::AddEventListeners() -> void {
    // When adding a game node to the scene, store it in an ordered set based
    // on the node’s level for efficient invocation of updates and events
    // without the need to traverse the entire graph.
    added_to_scene_listener_ = std::make_shared<EventListener>([&](Event* e) {
        auto scene_event = e->As<SceneEvent>();
        if (scene_event->node->Is<GameNode>()) {
            game_nodes_.emplace(CreateGameNodeRef(scene_event->node));
        }
    });

    // Remove game nodes from the ordered set as they're removed from the scene.
    removed_from_scene_listener_ = std::make_shared<EventListener>([&](Event* e) {
        auto scene_event = e->As<SceneEvent>();
        if (scene_event->node->Is<GameNode>()) {
            auto node = CreateGameNodeRef(scene_event->node);
            auto it = game_nodes_.find(node);
            if (it != end(game_nodes_)) game_nodes_.erase(node);
        }
    });

    // Dispatch keyboard events to game nodes hierarchically,
    // starting from the lowest level in the graph and moving upwards.
    keyboard_input_listener_ = std::make_shared<EventListener>([&](Event* e) {
        for (auto it = rbegin(game_nodes_); it != rend(game_nodes_); ++it) {
            if (e->handled) return;
            if (auto node = it->ptr.lock()) {
                node->As<GameNode>()->OnKeyboardEvent(e->As<KeyboardEvent>());
            }
        }
    });

    EventDispatcher::Get().AddEventListener("added_to_scene", added_to_scene_listener_);
    EventDispatcher::Get().AddEventListener("removed_from_scene", removed_from_scene_listener_);
    EventDispatcher::Get().AddEventListener("keyboard_event", keyboard_input_listener_);
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