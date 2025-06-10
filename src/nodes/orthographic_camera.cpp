/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/orthographic_camera.hpp"

namespace gleam {
    OrthographicCamera::OrthographicCamera(const Parameters& params) {
        projection_transform[0] = {2.0f / (params.right - params.left), 0.0f, 0.0f, 0.0f};
        projection_transform[1] = {0.0f, 2.0f / (params.top - params.bottom), 0.0f, 0.0f};
        projection_transform[2] = {0.0f, 0.0f, -2.0f / (params.far - params.near), 0.0f};
        projection_transform[3] = {
            -(params.right + params.left) / (params.right - params.left),
            -(params.top + params.bottom) / (params.top - params.bottom),
            -(params.far + params.near) / (params.far - params.near),
            1.0f
        };
    }
}