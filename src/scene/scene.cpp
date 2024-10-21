// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/scene.hpp"

#include "engine/scene/game_node.hpp"

#include "core/event.hpp"
#include "core/event_dispatcher.hpp"
#include "core/logger.hpp"

namespace engine {

Scene::Scene() {
    EventDispatcher::Get().AddEventListener("added_to_scene", [&](Event* e) {
        auto scene_event = e->As<SceneEvent>();
        if (scene_event->node->Is<GameNode>()) {
            game_nodes_.emplace(GameNodeReference {
                .uuid = scene_event->node->UUID(),
                .ptr = scene_event->node,
                .level = scene_event->node->level
            });
        }
    });
}

}