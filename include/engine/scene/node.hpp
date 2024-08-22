// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <memory>
#include <vector>

#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

class ENGINE_EXPORT Node {
public:
    auto Add(const std::shared_ptr<Node>& node) -> void;

    auto Remove(const std::shared_ptr<Node>& node) -> void;

    auto Children() const -> const std::vector<std::shared_ptr<Node>>&;

    auto Parent() const -> const Node*;

    auto GetTransform() const -> engine::Matrix4;

    auto Translate(const engine::Vector3& position) {
        position_ = position_ + position;
    }

    auto Scale(float value) {
        scale_ = engine::Vector3(value);
    }

private:
    Node* parent_ {nullptr};

    std::vector<std::shared_ptr<Node>> children_;

    engine::Matrix4 local_transform_ {1.0f};
    engine::Matrix4 world_transform_ {1.0f};
    engine::Vector3 position_ {0.0f};
    engine::Vector3 scale_ {1.0f};
};

}