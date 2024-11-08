// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/node.hpp"

#include "engine/core/logger.hpp"
#include "engine/math/transformations.hpp"

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

auto Node::UpdateLevel(const std::shared_ptr<Node>& node) -> void {
    node->level = node->parent_ == nullptr ? 0 : node->parent_->level + 1;
    for (auto& child : node->children_) {
        UpdateLevel(child);
    }
}

auto Node::Children() const -> const std::vector<std::shared_ptr<Node>>& {
    return children_;
}

auto Node::Parent() const -> const Node* {
    return parent_;
}

auto Node::ShouldUpdateChildren() const -> bool {
    return update_children_;
}

auto Node::GetWorldTransform() const -> Matrix4 {
    return world_transform_;
}

auto Node::UpdateTransforms() -> void {
    if (transformAutoUpdate && ShouldUpdateTransform()) {
        if (parent_ == nullptr) {
            world_transform_ = transform.ToMatrix();
        } else {
            world_transform_ = parent_->GetWorldTransform() * transform.ToMatrix();
        }
        // when update_children_ is set to true, we are ensuring that all the
        // nodes in this node’s subtree will update their world transforms,
        // even if no new transformations have been applied
        update_children_ = true;
    }

    // check for updates in child nodes, even if this node
    // doesn't require an update
    for (const auto child : children_) {
        if (child != nullptr) {
            child->UpdateTransforms();
        }
    }

    update_children_ = false;
}

auto Node::ShouldUpdateTransform() const -> bool {
    return transform.IsDirty() ||
           parent_ && parent_->ShouldUpdateChildren();
}

auto Node::Scale(float value) -> void {
    transform.Scale(value);
}

auto Node::RotateX(float distance) -> void {
    transform.Rotate(Vector3::Right(), distance);
}

auto Node::RotateY(float distance) -> void {
    transform.Rotate(Vector3::Up(), distance);
}

auto Node::RotateZ(float distance) -> void {
    transform.Rotate(Vector3::Forward(), distance);
}

auto Node::TranslateX(float distance) -> void {
    transform.Translate(Vector3::Right(), distance);
}

auto Node::TranslateY(float distance) -> void {
    transform.Translate(Vector3::Up(), distance);
}

auto Node::TranslateZ(float distance) -> void {
    transform.Translate(Vector3::Forward(), distance);
}

}