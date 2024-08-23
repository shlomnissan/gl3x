// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"
#include "engine/math/transform3d.hpp"

#include <memory>
#include <vector>

namespace engine {

class ENGINE_EXPORT Node {
public:
    auto Add(const std::shared_ptr<Node>& node) -> void;

    auto Remove(const std::shared_ptr<Node>& node) -> void;

    auto Children() const -> const std::vector<std::shared_ptr<Node>>&;

    auto Parent() const -> const Node*;

    auto GetTransform() -> engine::Matrix4;

    auto Scale(float value) -> void;

    auto TranslateX(float value) -> void;

    auto TranslateY(float value) -> void;

    auto TranslateZ(float value) -> void;

private:
    Node* parent_ {nullptr};

    std::vector<std::shared_ptr<Node>> children_;

    Transform3D local_transform_;

    Matrix4 world_transform_ {1.0f};
};

}