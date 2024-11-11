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
        HandleKeyboardInput(shared_from_this(), e->As<KeyboardEvent>());
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

auto Scene::HandleKeyboardInput(std::weak_ptr<Node> node, KeyboardEvent* event) -> void {
    // Events are propagated from the bottom of the scene graph to the top.
    // This allows nodes at the bottom of the graph to mark events as handled
    // and prevent them from being processed by parent nodes.
    if (const auto n = node.lock()) {
        for (const auto& child : n->Children()) {
            if (event->handled) return;
            HandleKeyboardInput(child, event);
        }
        n->OnKeyboardEvent(event);
    }
}

}