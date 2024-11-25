// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/euler.hpp"
#include "engine/math/vector3.hpp"

#include <math.h>

namespace engine {

Euler::Euler(float pitch, float yaw, float roll, RotationOrder order)
  : pitch_(pitch), yaw_(yaw), roll_(roll), order_(order) {}

auto Euler::GetMatrix() const -> Matrix4 {
    // TODO: generates the rotation matrix in place instead of performing
    // matrix multiplication for each rotation axis.
    const auto rotation_x = Rotate(Matrix4{1.0f}, pitch_, Vector3::Right());
    const auto rotation_y = Rotate(Matrix4{1.0f}, yaw_, Vector3::Up());
    const auto rotation_z = Rotate(Matrix4{1.0f}, roll_, Vector3::Forward());

    auto output = Matrix4 {0.0f};
    switch (order_) {
        case RotationOrder::XYZ:
            output = rotation_z * rotation_y * rotation_x;
            break;
        case RotationOrder::XZY:
            output = rotation_y * rotation_z * rotation_x;
            break;
        case RotationOrder::YXZ:
            output = rotation_z * rotation_x * rotation_y;
            break;
        case RotationOrder::YZX:
            output = rotation_x * rotation_z * rotation_y;
            break;
        case RotationOrder::ZXY:
            output = rotation_y * rotation_x * rotation_z;
            break;
        case RotationOrder::ZYX:
            output = rotation_x * rotation_y * rotation_z;
            break;
    }

    return output;
}

auto Euler::Rotate(const Matrix4& m, float angle, const Vector3& v) const -> Matrix4 {
    const auto a = angle;
    const auto c = std::cos(a);
    const auto s = std::sin(a);
    const auto axis = Normalize(v);
    const auto temp = (1.0f - c) * axis;

    auto rotate = engine::Matrix4 {};
    rotate[0] = {
        c + temp[0] * axis[0],
        temp[0] * axis[1] + s * axis[2],
        temp[0] * axis[2] - s * axis[1],
        0.0f
    };
    rotate[1] = {
        temp[1] * axis[0] - s * axis[2],
        c + temp[1] * axis[1],
        temp[1] * axis[2] + s * axis[0],
        0.0f
    };
    rotate[2] = {
        temp[2] * axis[0] + s * axis[1],
        temp[2] * axis[1] - s * axis[0],
        c + temp[2] * axis[2],
        0.0f
    };

    auto output = engine::Matrix4 {};
    output[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
    output[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
    output[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
    output[3] = m[3];
    return output;
}

}