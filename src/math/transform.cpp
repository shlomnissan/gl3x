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
    Euler rotation_euler {};
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
    return Vector3 { transform_[3] };
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
    if (forward == Vector3::Zero()) {
        // The position and target are the same, so we can't determine a forward vector.
        forward = Vector3::Forward();
    }

    auto right = Cross(world_up, forward);
    if (right.Length() == 0.0f) {
        // If the right vector is zero, the forward vector is parallel to the world up vector.
        if (std::abs(world_up.z) == 1.0f) {
            forward.x += 0.0001f;
        } else {
            forward.z += 0.0001f;
        }
        forward.Normalize();
        right = Cross(world_up, forward);
    }

    right.Normalize();
    auto up = Cross(forward, right);

    transform_[0] = {right, 0.0f};
    transform_[1] = {up, 0.0f};
    transform_[2] = {forward, 0.0f};
    touched = true;
}

}