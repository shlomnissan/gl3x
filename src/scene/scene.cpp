// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/scene.hpp"

#include "core/event.hpp"
#include "core/event_dispatcher.hpp"
#include "engine/core/logger.hpp"

#include <memory>
#include <vector>

namespace engine {

Scene::Scene() {
    AddEventListeners();
}

auto Scene::AddEventListeners() -> void {
    keyboard_event_listener_ = std::make_shared<EventListener>([&](Event* e) {
        HandleInputEvent(shared_from_this(), e);
    });
    EventDispatcher::Get().AddEventListener("keyboard_event", keyboard_event_listener_);

    mouse_event_listener_ = std::make_shared<EventListener>([&](Event* e) {
        HandleInputEvent(shared_from_this(), e);
    });
    EventDispatcher::Get().AddEventListener("mouse_event", mouse_event_listener_);
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

auto Scene::HandleInputEvent(std::weak_ptr<Node> node, Event* event) -> void {
    // Events are propagated from the bottom of the scene graph to the top.
    // This allows nodes at the bottom of the graph to mark events as handled
    // and prevent them from being processed by parent nodes.
    if (const auto n = node.lock()) {
        for (const auto& child : n->Children()) {
            if (event->handled) return;
            HandleInputEvent(child, event);
        }

        if (auto e = event->As<KeyboardEvent>()) n->OnKeyboardEvent(e);
        if (auto e = event->As<MouseEvent>()) n->OnMouseEvent(e);
    }
}

}