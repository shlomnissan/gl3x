// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/camera_perspective.hpp"
#include "engine/math/utilities.hpp"

#include <cmath>

namespace engine {
    CameraPerspective::CameraPerspective(
        float fov,
        float aspect,
        float near,
        float far
    ) :
        fov_(fov),
        aspect_(aspect)
    {
        near_ = near;
        far_ = far;
        CameraPerspective::UpdateProjectionTransform();
    }

    auto CameraPerspective::UpdateProjectionTransform() -> void {
        const auto tan_half_fov = std::tan((engine::math::DegToRad(fov_)) / 2);
        projection_transform_ = Matrix4 {1.0f};
        projection_transform_[0] = {1.0f / (aspect_ * tan_half_fov), 0.0f, 0.0f, 0.0f};
        projection_transform_[1] = {0.0f, 1.0f / tan_half_fov, 0.0f, 0.0f};
        projection_transform_[2] = {0.0f, 0.0f, -(far_ + near_) / (far_ - near_), -1.0f};
        projection_transform_[3] = {0.0f, 0.0f, -(2 * far_ * near_) / (far_ - near_), 0.0f};
    }
}