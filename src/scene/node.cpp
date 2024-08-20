// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "node.hpp"

#include <ranges>

namespace engine {

auto Node::add(const std::shared_ptr<Node>& node) -> void {
    if (node->parent_) {
        node->parent_->remove(node);
    }
    node->parent_ = this;
    children_.emplace_back(node);
}

auto Node::remove(const std::shared_ptr<Node>& node) -> void {
    auto it = std::ranges::find(children_, node);
    if (it != children_.end()) {
        children_.erase(it);
    }
    node->parent_ = nullptr;
}

auto Node::children() const -> const std::vector<std::shared_ptr<Node>>& {
    return children_;
}

}