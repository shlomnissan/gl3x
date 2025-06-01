// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/nodes/camera_perspective.hpp"
#include "gleam/math/utilities.hpp"

#include <cmath>

namespace gleam {
    CameraPerspective::CameraPerspective(const Parameters& params) : params_(params) {
        CameraPerspective::SetProjection();
    }

    auto CameraPerspective::SetProjection() -> void {
        const auto tan_half_fov = std::tan((gleam::math::DegToRad(params_.fov)) / 2);
        projection_transform[0] = {1.0f / (params_.aspect * tan_half_fov), 0.0f, 0.0f, 0.0f};
        projection_transform[1] = {0.0f, 1.0f / tan_half_fov, 0.0f, 0.0f};
        projection_transform[2] = {0.0f, 0.0f, -(params_.far + params_.near) / (params_.far - params_.near), -1.0f};
        projection_transform[3] = {0.0f, 0.0f, -(2 * params_.far * params_.near) / (params_.far - params_.near), 0.0f};
    }
}