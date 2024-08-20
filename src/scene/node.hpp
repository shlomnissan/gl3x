// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <memory>
#include <vector>

// TODO:
// - move node to the public include folder
// - add tests
// - error handling for remove
// - thread safety (add mutex, lock guard for adding/removing/access children)

namespace engine {

class ENGINE_EXPORT Node {
public:
    auto add(const std::shared_ptr<Node>& node) -> void;

    auto remove(const std::shared_ptr<Node>& node) -> void;

    auto children() const -> const std::vector<std::shared_ptr<Node>>&;

private:
    Node* parent_ {nullptr};

    std::vector<std::shared_ptr<Node>> children_;
};

}