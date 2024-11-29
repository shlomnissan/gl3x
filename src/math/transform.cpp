// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform.hpp"

#include "engine/math/euler.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"
#include "engine/math/utilities.hpp"

#include <cmath>

namespace engine {

auto Transform::Scale(float value) -> void {
    Scale({value, value, value});
}

auto Transform::Scale(const Vector3& value) -> void {
    transform_[0] *= value.x;
    transform_[1] *= value.y;
    transform_[2] *= value.z;
    touched = true;
}

auto Transform::Translate(const Vector3& value) -> void {
    transform_[3] = transform_[0] * value.x + transform_[1] * value.y + transform_[2] * value.z + transform_[3];
    touched = true;
}

auto Transform::Rotate(const Vector3& axis, float angle) -> void {
    Euler rotation_euler(0.0f, 0.0f, 0.0f);
    if (axis == Vector3::Right()) {
        rotation_euler.pitch = angle;
    } else if (axis == Vector3::Up()) {
        rotation_euler.yaw = angle;
    } else if (axis == Vector3::Forward()) {
        rotation_euler.roll = angle;
    }
    transform_ = transform_ * rotation_euler.GetMatrix();
    touched = true;
}

auto Transform::GetPosition() const -> Vector3 {
    return transform_[3];
}

auto Transform::SetPosition(const Vector3& position) -> void {
    transform_[3] = {position.x, position.y, position.z, 1.0f};
    touched = true;
}

auto Transform::GetScale() const -> Vector3 {
    return {
        transform_[0].Length(),
        transform_[1].Length(),
        transform_[2].Length()
    };
}

auto Transform::LookAt(const Vector3& position, const Vector3& target, const Vector3& world_up) -> void {
    auto forward = Normalize(position - target);
    // TODO: handle case where position and target are the same

    auto right = Normalize(Cross(world_up, forward));
    // TODO: handle case where world_up and forward are parallel

    auto up = Cross(forward, right);

    transform_[0] = {right.x, right.y, right.z, 0.0f};
    transform_[1] = {up.x, up.y, up.z, 0.0f};
    transform_[2] = {forward.x, forward.y, forward.z, 0.0f};
    touched = true;
}

auto Transform::Perspective(float fov, float aspect_ratio, float near, float far) -> void {
    const auto tan_half_fov = std::tan((engine::math::DegToRad(fov)) / 2);
    transform_[0] = {1.0f / (aspect_ratio * tan_half_fov), 0.0f, 0.0f, 0.0f};
    transform_[1] = {0.0f, 1.0f / tan_half_fov, 0.0f, 0.0f};
    transform_[2] = {0.0f, 0.0f, -(far + near) / (far - near), -1.0f};
    transform_[3] = {0.0f, 0.0f, -(2 * far * near) / (far - near), 0.0f};
    touched = true;
}

auto Transform::Orthographic(float left, float right, float bottom, float top, float near, float far) -> void {
    transform_[0] = {2.0f / (right - left), 0.0f, 0.0f, 0.0f};
    transform_[1] = {0.0f, 2.0f / (top - bottom), 0.0f, 0.0f};
    transform_[2] = {0.0f, 0.0f, -2.0f / (far - near), 0.0f};
    transform_[3] = {
        -(right + left) / (right - left),
        -(top + bottom) / (top - bottom),
        -(far + near) / (far - near),
        1.0f
    };
    touched = true;
}

}