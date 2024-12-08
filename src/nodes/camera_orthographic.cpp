// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/nodes/camera_orthographic.hpp"

namespace engine {
    CameraOrthographic::CameraOrthographic(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far
    ) {
        projection_transform.Orthographic(left, right, bottom, top, near, far);
    }
}