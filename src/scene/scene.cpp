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
    keyboard_input_listener_ = std::make_shared<EventListener>([&](Event* e) {
        // TODO: dispatch event to nodes
    });

    EventDispatcher::Get().AddEventListener("keyboard_input", keyboard_input_listener_);
}

auto Scene::ProcessUpdates(double delta) -> void {
    HandleNodeUpdates(shared_from_this(), delta);
}

auto Scene::HandleNodeUpdates(std::weak_ptr<Node> node, double delta) -> void {
    if (const auto n = node.lock()) {
        n->Update(delta);
        for (const auto& child : n->Children()) {
            HandleNodeUpdates(child, delta);
        }
    }
}

}