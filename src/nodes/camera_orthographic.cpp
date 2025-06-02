/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/camera_orthographic.hpp"

namespace gleam {
    CameraOrthographic::CameraOrthographic(const Parameters& params) : params_(params) {
        CameraOrthographic::SetProjection();
    }

    auto CameraOrthographic::SetProjection() -> void {
        projection_transform[0] = {2.0f / (params_.right - params_.left), 0.0f, 0.0f, 0.0f};
        projection_transform[1] = {0.0f, 2.0f / (params_.top - params_.bottom), 0.0f, 0.0f};
        projection_transform[2] = {0.0f, 0.0f, -2.0f / (params_.far - params_.near), 0.0f};
        projection_transform[3] = {
            -(params_.right + params_.left) / (params_.right - params_.left),
            -(params_.top + params_.bottom) / (params_.top - params_.bottom),
            -(params_.far + params_.near) / (params_.far - params_.near),
            1.0f
        };
    }
}