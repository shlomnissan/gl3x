// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/scene.hpp"

#include "engine/core/logger.hpp"

#include <vector>

namespace engine {

Scene::Scene() {
    AddEventListeners();
}

auto Scene::AddEventListeners() -> void {
    // Dispatch keyboard events to game nodes hierarchically,
    // starting from the lowest level in the graph and moving upwards.
    keyboard_input_listener_ = std::make_shared<EventListener>([&](Event* e) {
        // TODO: iterate through the scene's game nodes and dispatch the event
    });

    EventDispatcher::Get().AddEventListener("keyboard_input", keyboard_input_listener_);
}

auto Scene::Update(double delta) -> void {
    for (const auto& node : Children()) {
        ProcessUpdates(node, delta);
    }
}

auto Scene::ProcessUpdates(std::weak_ptr<Node> node, double delta) -> void {
    if (const auto n = node.lock()) {
        n->Update(delta);
        for (const auto& child : n->Children()) {
            ProcessUpdates(child, delta);
        }
    }
}

}