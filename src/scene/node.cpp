// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/node.hpp"
#include "engine/math/transformations.hpp"

#include <ranges>

namespace engine {

auto Node::Add(const std::shared_ptr<Node>& node) -> void {
    if (node->parent_) {
        node->parent_->Remove(node);
    }
    node->parent_ = this;
    children_.emplace_back(node);
}

auto Node::Remove(const std::shared_ptr<Node>& node) -> void {
    auto it = std::ranges::find(children_, node);
    if (it != children_.end()) {
        children_.erase(it);
    }
    node->parent_ = nullptr;
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
    if (ShouldUpdateTransform()) {
        if (parent_ == nullptr) {
            world_transform_ = local_transform_.ToMatrix();
        } else {
            world_transform_ = parent_->GetWorldTransform() * local_transform_.ToMatrix();
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
    return local_transform_.IsDirty() ||
           parent_ && parent_->ShouldUpdateChildren();
}

auto Node::Scale(float value) -> void {
    local_transform_.Scale(value);
}

auto Node::RotateX(float distance) -> void {
    local_transform_.Rotate(Vector3::X(), distance);
}

auto Node::RotateY(float distance) -> void {
    local_transform_.Rotate(Vector3::Y(), distance);
}

auto Node::RotateZ(float distance) -> void {
    local_transform_.Rotate(Vector3::Z(), distance);
}

auto Node::TranslateX(float distance) -> void {
    local_transform_.Translate(Vector3::X(), distance);
}

auto Node::TranslateY(float distance) -> void {
    local_transform_.Translate(Vector3::Y(), distance);
}

auto Node::TranslateZ(float distance) -> void {
    local_transform_.Translate(Vector3::Z(), distance);
}

}