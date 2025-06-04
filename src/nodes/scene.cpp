/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/scene.hpp"

#include "core/event_dispatcher.hpp"
#include "utilities/logger.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace gleam {

Scene::Scene() {
    AddEventListeners();
}

auto Scene::AddEventListeners() -> void {
    using enum EventType;

    scene_event_listener_ = std::make_shared<EventListener>([&](Event* event) {
        HandleSceneEvents(static_cast<SceneEvent*>(event));
    });

    input_event_listener_ = std::make_shared<EventListener>([&](Event* event) {
        for (const auto& child : Children()) {
            HandleInputEvent(child, event);
        }
        if (event->handled) return;

        const auto type = event->GetType();
        if (type == Keyboard) OnKeyboardEvent(static_cast<KeyboardEvent*>(event));
        if (type == Mouse) OnMouseEvent(static_cast<MouseEvent*>(event));
    });

    EventDispatcher::Get().AddEventListener("node_added", scene_event_listener_);
    EventDispatcher::Get().AddEventListener("node_removed", scene_event_listener_);
    EventDispatcher::Get().AddEventListener("keyboard_event", input_event_listener_);
    EventDispatcher::Get().AddEventListener("mouse_event", input_event_listener_);
}

auto Scene::ProcessUpdates(float delta) -> void {
    OnUpdate(delta);
     for (const auto& child : Children()) {
        HandleNodeUpdates(child, delta);
    }
}

auto Scene::HandleNodeUpdates(std::weak_ptr<Node> node, float delta) -> void {
    if (const auto n = node.lock()) {
        n->OnUpdate(delta);
        for (const auto& child : n->Children()) {
            HandleNodeUpdates(child, delta);
        }
    }
}

auto Scene::HandleInputEvent(std::weak_ptr<Node> node, Event* event) -> void {
    using enum EventType;

    // Events are propagated from the bottom of the scene graph to the top.
    // This allows nodes at the bottom of the graph to mark events as handled
    // and prevent them from being processed by parent nodes.
    if (const auto n = node.lock()) {
        for (const auto& child : n->Children()) {
            if (event->handled) return;
            HandleInputEvent(child, event);
        }

        const auto type = event->GetType();
        if (type == Keyboard) n->OnKeyboardEvent(static_cast<KeyboardEvent*>(event));
        if (type == Mouse) n->OnMouseEvent(static_cast<MouseEvent*>(event));
    }
}

auto Scene::HandleSceneEvents(const SceneEvent* event) -> void {
    using enum SceneEvent::Type;
    if (IsChild(event->node.get())) {
        touched_ = true;
        if (event->type == NodeAdded) event->node->AttachRecursive(context_);
        if (event->type == NodeRemoved) event->node->DetachRecursive();
    }
}

auto Scene::SetContext(SharedContext* context) -> void {
    this->AttachRecursive(context);
}

Scene::~Scene() {
    EventDispatcher::Get().RemoveEventListener("node_added", scene_event_listener_);
    EventDispatcher::Get().RemoveEventListener("node_removed", scene_event_listener_);
    EventDispatcher::Get().RemoveEventListener("keyboard_event", input_event_listener_);
    EventDispatcher::Get().RemoveEventListener("mouse_event", input_event_listener_);
}

}