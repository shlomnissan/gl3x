// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/nodes/camera_perspective.hpp"
#include "engine/math/utilities.hpp"

#include <cmath>

namespace engine {
    CameraPerspective::CameraPerspective(const Parameters& params) {
        SetProjection(params);
    }

    auto CameraPerspective::SetProjection(const Parameters& params) -> void {
        const auto tan_half_fov = std::tan((engine::math::DegToRad(params.fov)) / 2);
        projection_transform[0] = {1.0f / (params.aspect * tan_half_fov), 0.0f, 0.0f, 0.0f};
        projection_transform[1] = {0.0f, 1.0f / tan_half_fov, 0.0f, 0.0f};
        projection_transform[2] = {0.0f, 0.0f, -(params.far + params.near) / (params.far - params.near), -1.0f};
        projection_transform[3] = {0.0f, 0.0f, -(2 * params.far * params.near) / (params.far - params.near), 0.0f};
    }
}