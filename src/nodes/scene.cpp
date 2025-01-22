// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/nodes/scene.hpp"

#include "core/event.hpp"
#include "core/event_dispatcher.hpp"
#include "utilities/logger.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace engine {

Scene::Scene() {
    AddEventListeners();
}

auto Scene::AddEventListeners() -> void {
    scene_event_listener_ = std::make_shared<EventListener>([&](Event* e) {
        HandleSceneEvents(e->As<SceneEvent>());
    });

    input_event_listener_ = std::make_shared<EventListener>([&](Event* e) {
        HandleInputEvent(shared_from_this(), e);
    });

    EventDispatcher::Get().AddEventListener("added_to_scene", scene_event_listener_);
    EventDispatcher::Get().AddEventListener("removed_from_scene", scene_event_listener_);
    EventDispatcher::Get().AddEventListener("keyboard_event", input_event_listener_);
    EventDispatcher::Get().AddEventListener("mouse_event", input_event_listener_);
}

auto Scene::ProcessUpdates(float delta) -> void {
    HandleNodeUpdates(shared_from_this(), delta);
}

auto Scene::HandleNodeUpdates(std::weak_ptr<Node> node, float delta) -> void {
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

auto Scene::HandleSceneEvents(const SceneEvent* event) -> void {
    touched_ = true;
}

Scene::~Scene() {
    EventDispatcher::Get().RemoveEventListener("added_to_scene", scene_event_listener_);
    EventDispatcher::Get().RemoveEventListener("removed_from_scene", scene_event_listener_);
    EventDispatcher::Get().RemoveEventListener("keyboard_event", input_event_listener_);
    EventDispatcher::Get().RemoveEventListener("mouse_event", input_event_listener_);
}

}