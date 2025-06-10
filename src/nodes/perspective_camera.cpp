/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/perspective_camera.hpp"
#include "gleam/math/utilities.hpp"

#include <cmath>

namespace gleam {
    PerspectiveCamera::PerspectiveCamera(const Parameters& params) {
        const auto tan_half_fov = std::tan((gleam::math::DegToRad(params.fov)) / 2);
        projection_transform[0] = {1.0f / (params.aspect * tan_half_fov), 0.0f, 0.0f, 0.0f};
        projection_transform[1] = {0.0f, 1.0f / tan_half_fov, 0.0f, 0.0f};
        projection_transform[2] = {0.0f, 0.0f, -(params.far + params.near) / (params.far - params.near), -1.0f};
        projection_transform[3] = {0.0f, 0.0f, -(2 * params.far * params.near) / (params.far - params.near), 0.0f};
    }
}