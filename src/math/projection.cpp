// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/projection.hpp>

#include <cmath>

namespace engine {

auto ortho(float left, float right, float bottom, float top, float near, float far) -> Matrix4 {
    auto output = Matrix4 {1.0f};
    output[0] = {2.0f / (right - left), 0.0f, 0.0f, 0.0f};
    output[1] = {0.0f, 2.0f / (top - bottom), 0.0f, 0.0f};
    output[2] = {0.0f, 0.0f, -2.0f / (far - near), 0.0f};
    output[3] = {
        -(right + left) / (right - left),
        -(top + bottom) / (top - bottom),
        -(far + near) / (far - near),
        1.0f
    };
    return output;
}

auto perspective(float fov, float aspect_ratio, float near, float far) -> Matrix4 {
    const auto tan_half_fov = std::tan(fov / 2);
    auto output = Matrix4 {0.0f};
    output[0] = {1 / (aspect_ratio * tan_half_fov), 0.0f, 0.0f, 0.0f};
    output[1] = {0.0f, 1 / tan_half_fov, 0.0f, 0.0f};
    output[2] = {0.0f, 0.0f, -(far + near) / (far - near), -1.0f};
    output[3] = {0.0f, 0.0f, -(2 * far * near) / (far - near), 0.0f};
    return output;
}

}