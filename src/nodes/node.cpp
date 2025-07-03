/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/node.hpp"

#include "gleam/cameras/camera.hpp"

#include "events/event_dispatcher.hpp"
#include "utilities/logger.hpp"

#include <queue>
#include <ranges>

namespace gleam {

auto Node::Add(const std::shared_ptr<Node>& node) -> void {
    if (node->parent_) {
        node->parent_->Remove(node);
    }
    node->parent_ = this;
    children_.emplace_back(node);

    EventDispatcher::Get().Dispatch(
        "node_added",
        std::make_unique<SceneEvent>(SceneEvent::Type::NodeAdded, node)
    );
}

auto Node::Remove(const std::shared_ptr<Node>& node) -> void {
    auto it = std::ranges::find(children_, node);
    if (it != children_.end()) {
        EventDispatcher::Get().Dispatch(
            "node_removed",
            std::make_unique<SceneEvent>(SceneEvent::Type::NodeRemoved, node)
        );
        children_.erase(it);
        node->parent_ = nullptr;
        node->transform.touched = true;
    } else {
        Logger::Log(
            LogLevel::Warning,
            "Attempting to remove a node that was not added to the graph {}",
            *node
        );
    }
}

auto Node::RemoveAllChildren() -> void {
    for (const auto& node : children_) {
        EventDispatcher::Get().Dispatch(
            "node_removed",
            std::make_unique<SceneEvent>(SceneEvent::Type::NodeRemoved, node)
        );
        node->parent_ = nullptr;
    }
    children_.clear();
}

auto Node::Children() -> std::vector<std::shared_ptr<Node>>& {
    return children_;
}

auto Node::IsChild(const Node* node) const -> bool {
    auto to_process = std::queue<std::shared_ptr<Node>>();
    for (const auto& child : children_) {
        to_process.push(child);
    }

    while (!to_process.empty()) {
        auto len = to_process.size();
        for (auto i = 0; i < len; ++i) {
            const auto current = to_process.front();
            to_process.pop();
            if (current.get() == node) return true;
            for (const auto& child : current->children_) {
                to_process.push(child);
            }
        }
    }

    return false;
}

auto Node::Parent() const -> const Node* {
    return parent_;
}

auto Node::UpdateTransformHierarchy() -> void {
    if (transform_auto_update && ShouldUpdateWorldTransform()) {
        world_transform_ = parent_ == nullptr
            ? transform.Get()
            : parent_->world_transform_ * transform.Get();
        transform.touched = false;
        world_transform_touched_ = true;
    }

    for (const auto child : children_) {
        if (child != nullptr) {
            child->UpdateTransformHierarchy();
        }
    }

    world_transform_touched_ = false;
}

auto Node::UpdateWorldTransform() -> void {
    if (parent_ != nullptr) {
        parent_->UpdateWorldTransform();
    }

    if (ShouldUpdateWorldTransform()) {
        world_transform_ = parent_ == nullptr
            ? transform.Get()
            : parent_->world_transform_ * transform.Get();
        transform.touched = false;
    }
}

auto Node::ShouldUpdateWorldTransform() const -> bool {
    return transform.touched || (parent_ && parent_->world_transform_touched_);
}

auto Node::GetWorldPosition() -> Vector3 {
    UpdateWorldTransform();
    return Vector3(world_transform_[3]);
}

auto Node::GetWorldTransform() -> Matrix4 {
    if (transform_auto_update) {
        UpdateTransformHierarchy();
    }
    return world_transform_;
}

auto Node::Context() const -> SharedContext* {
    if (context_ == nullptr) {
        Logger::Log(
            LogLevel::Error,
            "Shared context is not set. Ensure the node is part of an active "
            "scene and that the context is accessed after the node is initialized. "
            "The context is guaranteed to be initialized after the node is attached "
            "to an active scene which invokes the OnAttached() method."
        );
        return nullptr;
    }
    return context_;
}

auto Node::LookAt(const Vector3& target) -> void {
    const auto position = GetWorldPosition();
    GetNodeType() == NodeType::CameraNode
        ? transform.LookAt(position, target, up)
        : transform.LookAt(target, position, up);
}

auto Node::AttachRecursive(SharedContext* context) -> void {
    context_ = context;
    OnAttached();
    for (const auto& child : children_) {
        if (child != nullptr) {
            child->AttachRecursive(context);
        }
    }
}

auto Node::DetachRecursive() -> void {
    context_ = nullptr;
    for (const auto& child : children_) {
        if (child != nullptr) {
            child->DetachRecursive();
        }
    }
}

}