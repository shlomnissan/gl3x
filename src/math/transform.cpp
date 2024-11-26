// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform.hpp"

#include "engine/math/euler.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

auto Transform::Scale(float value) -> void {
    Scale({value, value, value});
}

auto Transform::Scale(const Vector3& value) -> void {
    transform_[0] *= value.x;
    transform_[1] *= value.y;
    transform_[2] *= value.z;
    is_dirty_ = true;
}

auto Transform::Translate(const Vector3& value) -> void {
    transform_[3] = transform_[0] * value.x + transform_[1] * value.y + transform_[2] * value.z + transform_[3];
    is_dirty_ = true;
}

auto Transform::Rotate(const Vector3& axis, float angle) -> void {
    Euler rotation_euler(0.0f, 0.0f, 0.0f);
    if (axis == Vector3::Right()) {
        rotation_euler.pitch_ = angle;
    } else if (axis == Vector3::Up()) {
        rotation_euler.yaw_ = angle;
    } else if (axis == Vector3::Forward()) {
        rotation_euler.roll_ = angle;
    }
    transform_ = transform_ * rotation_euler.GetMatrix();
    is_dirty_ = true;
}

auto Transform::Get() -> Matrix4 {
    if (is_dirty_) is_dirty_ = false;
    return transform_;
}

auto Transform::GetPosition() const -> Vector3 {
    return transform_[3];
}

auto Transform::GetScale() const -> Vector3 {
    return {
        transform_[0].Length(),
        transform_[1].Length(),
        transform_[2].Length()
    };
}

}