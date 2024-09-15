// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/euler.hpp"
#include "engine/math/transformations.hpp"
#include "engine/math/vector3.hpp"

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

}