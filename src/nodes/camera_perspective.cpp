// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/nodes/camera_perspective.hpp"
#include "engine/math/utilities.hpp"

#include <cmath>

namespace engine {
    CameraPerspective::CameraPerspective(
        float fov,
        float aspect,
        float near,
        float far
    ) {
        projection_transform.Perspective(fov, aspect, near, far);
    }
}