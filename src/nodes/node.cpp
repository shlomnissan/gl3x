// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/nodes/node.hpp"

#include "engine/nodes/camera.hpp"

#include "core/event_dispatcher.hpp"
#include "utilities/logger.hpp"

#include <ranges>

namespace engine {

auto Node::Add(const std::shared_ptr<Node>& node) -> void {
    if (node->parent_) {
        node->parent_->Remove(node);
    }
    node->parent_ = this;
    children_.emplace_back(node);
    UpdateLevel(node);

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
        UpdateLevel(node);
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
        UpdateLevel(node);
    }
    children_.clear();
}

auto Node::UpdateLevel(const std::shared_ptr<Node>& node) -> void {
    node->level = node->parent_ == nullptr ? 0 : node->parent_->level + 1;
    for (const auto& child : node->children_) {
        UpdateLevel(child);
    }
}

auto Node::Children() const -> const std::vector<std::shared_ptr<Node>>& {
    return children_;
}

auto Node::Parent() const -> const Node* {
    return parent_;
}

auto Node::UpdateTransformHierarchy() -> void {
    if (transformAutoUpdate && ShouldUpdateWorldTransform()) {
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

auto Node::LookAt(const Vector3& target) -> void {
    UpdateWorldTransform();
    const auto position = GetWorldPosition();
    if (this->Is<Camera>()) {
        transform.LookAt(position, target, up);
    } else {
        transform.LookAt(target, position, up);
    }
}

}