// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/camera_orthographic.hpp"

namespace engine {
    CameraOrthographic::CameraOrthographic(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    ) :
        left_(left),
        right_(right),
        bottom_(bottom),
        top_(top)
    {
        near_ = near;
        far_ = far;
        UpdateProjectionTransform();
    }

    auto CameraOrthographic::UpdateProjectionTransform() -> void {
        projection_transform_ = Matrix4 {1.0f};
        projection_transform_[0] = {2.0f / (right_ - left_), 0.0f, 0.0f, 0.0f};
        projection_transform_[1] = {0.0f, 2.0f / (top_ - bottom_), 0.0f, 0.0f};
        projection_transform_[2] = {0.0f, 0.0f, -2.0f / (far_ - near_), 0.0f};
        projection_transform_[3] = {
            -(right_ + left_) / (right_ - left_),
            -(top_ + bottom_) / (top_ - bottom_),
            -(far_ + near_) / (far_ - near_),
            1.0f
        };
    }
}