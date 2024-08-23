// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/node.hpp"

#include <ranges>

#include "engine/math/transformations.hpp"

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

auto Node::GetTransform() -> engine::Matrix4 {
    return world_transform_ * local_transform_.Get();
}

auto Node::Scale(float value) -> void {
    local_transform_.Scale(value);
}

auto Node::TranslateX(float value) -> void {
    local_transform_.Translate(Vector3::X(), value);
}

auto Node::TranslateY(float value) -> void {
    local_transform_.Translate(Vector3::Y(), value);
}

auto Node::TranslateZ(float value) -> void {
    local_transform_.Translate(Vector3::Z(), value);
}

}