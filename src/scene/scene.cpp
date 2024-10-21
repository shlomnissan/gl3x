// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/scene.hpp"

#include "core/event.hpp"
#include "core/event_dispatcher.hpp"
#include "core/logger.hpp"

namespace engine {

Scene::Scene() {
    EventDispatcher::Get().AddEventListener("added_to_scene", [](Event* e) {
        auto scene_event = e->As<SceneEvent>();
        // TODO: handle event
    });

    EventDispatcher::Get().AddEventListener("removed_from_scene", [](Event* e) {
        auto scene_event = e->As<SceneEvent>();
        // TODO: handle event
    });
}

}