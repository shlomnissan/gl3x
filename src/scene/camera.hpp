// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/matrix4.hpp"
#include "engine/scene/node.hpp"

namespace engine {

class Camera : public Node {
public:
    auto GetProjectionMatrix() const { return projection_transform_; }

    auto GetViewMatrix() const { return view_transform_; }

    virtual ~Camera() = default;

protected:
    float near_;
    float far_;

    Matrix4 projection_transform_;

    // Inverse of the world transform attached to the node
    Matrix4 view_transform_;

    virtual auto UpdateProjectionTransform() -> void = 0;
};

}