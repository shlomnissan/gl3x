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
        // TODO: generate projection transform (projection_transform_)
    }
}