// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/node.hpp"

#include "engine/core/logger.hpp"
#include "engine/scene/camera.hpp"

#include "core/event_dispatcher.hpp"

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

auto Node::UpdateTransforms(bool update_parents, bool update_children) -> void {
    if (update_parents && parent_ != nullptr) {
        parent_->UpdateTransforms(true, false);
    }

    if (transformAutoUpdate && ShouldUpdateWorldTransform()) {
        if (parent_ == nullptr) {
            world_transform = transform;
        } else {
            world_transform = parent_->world_transform * transform;
        }
        transform.touched = false;
        world_transform.touched = true;
    }

    // check for updates in child nodes, even if this node doesn't require an update
    if (update_children) {
        for (const auto child : children_) {
            if (child != nullptr) {
                child->UpdateTransforms();
            }
        }
    }

    world_transform.touched = false;
}

auto Node::ShouldUpdateWorldTransform() const -> bool {
    return transform.touched || (parent_ && parent_->world_transform.touched);
}

auto Node::GetWorldPosition() -> Vector3 {
    UpdateTransforms(true, false);
    return world_transform.GetPosition();
}

auto Node::LookAt(const Vector3& target) -> void {
    UpdateTransforms(true, false);
    const auto position = GetWorldPosition();
    if (this->Is<Camera>()) {
        transform.LookAt(position, target, up);
    } else {
        transform.LookAt(target, position, up);
    }
}

}