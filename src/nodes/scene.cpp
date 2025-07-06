/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/scene.hpp"

#include "events/event_dispatcher.hpp"
#include "utilities/logger.hpp"

namespace gleam {

namespace {

auto handle_node_updates(std::weak_ptr<Node> node, float delta) -> void {
    if (const auto n = node.lock()) {
        n->OnUpdate(delta);
        for (const auto& child : n->Children()) {
            handle_node_updates(child, delta);
        }
    }
}

auto handle_input_event(std::weak_ptr<Node> node, Event* event) -> void {
    using enum EventType;

    // Events are propagated from the bottom of the scene graph to the top.
    // This allows nodes at the bottom of the graph to mark events as handled
    // and prevent them from being processed by parent nodes.
    if (const auto n = node.lock()) {
        for (const auto& child : n->Children()) {
            if (event->handled) return;
            handle_input_event(child, event);
        }

        const auto type = event->GetType();
        if (type == Keyboard) n->OnKeyboardEvent(static_cast<KeyboardEvent*>(event));
        if (type == Mouse) n->OnMouseEvent(static_cast<MouseEvent*>(event));
    }
}

}

struct Scene::Impl {
    std::shared_ptr<EventListener> input_event_listener;
    std::shared_ptr<EventListener> scene_event_listener;
};

Scene::Scene() : impl_(std::make_unique<Impl>()) {
    using enum EventType;

    impl_->scene_event_listener = std::make_shared<EventListener>([&](Event* event) {
        using enum SceneEvent::Type;

        auto e = static_cast<SceneEvent*>(event);
        if (IsChild(e->node.get())) {
            touched_ = true;
            if (e->type == NodeAdded) e->node->AttachRecursive(context_);
            if (e->type == NodeRemoved) e->node->DetachRecursive();
        }
    });

    impl_->input_event_listener = std::make_shared<EventListener>([&](Event* event) {
        for (const auto& child : Children()) {
            handle_input_event(child, event);
        }
        if (event->handled) return;

        const auto type = event->GetType();
        if (type == Keyboard) OnKeyboardEvent(static_cast<KeyboardEvent*>(event));
        if (type == Mouse) OnMouseEvent(static_cast<MouseEvent*>(event));
    });

    EventDispatcher::Get().AddEventListener("node_added", impl_->scene_event_listener);
    EventDispatcher::Get().AddEventListener("node_removed", impl_->scene_event_listener);
    EventDispatcher::Get().AddEventListener("keyboard_event", impl_->input_event_listener);
    EventDispatcher::Get().AddEventListener("mouse_event", impl_->input_event_listener);
}

auto Scene::ProcessUpdates(float delta) -> void {
    OnUpdate(delta);
     for (const auto& child : Children()) {
        handle_node_updates(child, delta);
    }
}

auto Scene::SetContext(SharedContext* context) -> void {
    this->AttachRecursive(context);
}

Scene::~Scene() {
    EventDispatcher::Get().RemoveEventListener("node_added", impl_->scene_event_listener);
    EventDispatcher::Get().RemoveEventListener("node_removed", impl_->scene_event_listener);
    EventDispatcher::Get().RemoveEventListener("keyboard_event", impl_->input_event_listener);
    EventDispatcher::Get().RemoveEventListener("mouse_event", impl_->input_event_listener);
}

}