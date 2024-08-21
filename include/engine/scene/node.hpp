// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <memory>
#include <vector>

namespace engine {

class ENGINE_EXPORT Node {
public:
    auto Add(const std::shared_ptr<Node>& node) -> void;

    auto Remove(const std::shared_ptr<Node>& node) -> void;

    auto Children() const -> const std::vector<std::shared_ptr<Node>>&;

    auto Parent() const -> const Node*;

private:
    Node* parent_ {nullptr};

    std::vector<std::shared_ptr<Node>> children_;
};

}