// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/matrix4.hpp"
#include "engine/nodes/node.hpp"

namespace engine {

class Camera : public Node {
public:
    Matrix4 projection_transform;

    Matrix4 view_transform;

    auto UpdateViewTransform() -> void;

    virtual ~Camera() = default;
};

}