// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/math/matrix4.hpp"
#include "engine/scene/node.hpp"

namespace engine {

class Camera : public Node {
public:
    virtual auto updateProjectionTransform() -> void = 0;

    virtual ~Camera() = default; 

private:
    Matrix4 projection_transform_;

    Matrix4 world_transform_inverse_;
};

}