// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/nodes/node.hpp"

#include "engine/nodes/camera.hpp"

#include "core/event_dispatcher.hpp"
#include "utilities/logger.hpp"

#include <queue>
#include <ranges>

namespace engine {

auto Node::Add(const std::shared_ptr<Node>& node) -> void {
    if (node->parent_) {
        node->parent_->Remove(node);
    }
    node->parent_ = this;
    children_.emplace_back(node);

    EventDispatcher::Get().Dispatch(
        "added_to_scene",
        std::make_unique<SceneEvent>(SceneEvent::Type::AddedToScene, node)
    );
}

auto Node::Remove(const std::shared_ptr<Node>& node) -> void {
    auto it = std::ranges::find(children_, node);
    if (it != children_.end()) {
        EventDispatcher::Get().Dispatch(
            "removed_from_scene",
            std::make_unique<SceneEvent>(SceneEvent::Type::RemovedFromScene, node)
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
            "removed_from_scene",
            std::make_unique<SceneEvent>(SceneEvent::Type::RemovedFromScene, node)
        );
        node->parent_ = nullptr;
    }
    children_.clear();
}

auto Node::Children() -> std::vector<std::shared_ptr<Node>>& {
    return children_;
}

auto Node::IsChild(const Node* node) const -> bool {
    auto to_process = std::queue<const Node*>();
    for (const auto child : children_) {
        if (child != nullptr) to_process.push(child.get());
    }

    while (!to_process.empty()) {
        for (auto i = 0; i < to_process.size(); ++i) {
            const auto current = to_process.front();
            to_process.pop();
            if (current == node) return true;
            for (const auto child : current->children_) {
                if (child != nullptr) to_process.push(child.get());
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

auto Node::LookAt(const Vector3& target) -> void {
    const auto position = GetWorldPosition();
    if (this->Is<Camera>()) {
        transform.LookAt(position, target, up);
    } else {
        transform.LookAt(target, position, up);
    }
}

}