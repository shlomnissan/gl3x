// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform_3d.hpp"

#include <cmath>

namespace engine {

auto Transform3D::Translate(const Vector3& value) -> void {
    position_ += value;
    touched = true;
}

auto Transform3D::Rotate(const Vector3& axis, float angle) -> void {
    assert(axis == Vector3::Right() || axis == Vector3::Up() || axis == Vector3::Forward());
    if (axis == Vector3::Right()) {
        rotation_.pitch += angle;
    }else if (axis == Vector3::Up()) {
        rotation_.yaw += angle;
    } else if (axis == Vector3::Forward()) {
        rotation_.roll += angle;
    }
    touched = true;
}

auto  Transform3D::LookAt(const Vector3& position, const Vector3& target, const Vector3& world_up) -> void {
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

    rotation_ = Euler {{
        right.x, up.x, forward.x, 0.0f,
        right.y, up.y, forward.y, 0.0f,
        right.z, up.z, forward.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }};

    touched = true;
}

auto Transform3D::SetPosition(const Vector3& position) -> void {
    if (position_ != position) {
        position_ = position;
        touched = true;
    }
}

auto Transform3D::SetScale(const Vector3& scale) -> void {
    if (scale_ != scale) {
        scale_ = scale;
        touched = true;
    }
}

auto Transform3D::SetRotation(const Euler& rotation) -> void {
    if (rotation_ != rotation) {
        rotation_ = rotation;
        touched = true;
    }
}

auto Transform3D::Get() -> Matrix4 {
    if (touched) {
        auto translate = Matrix4 {
            1.0f, 0.0f, 0.0f, position_.x,
            0.0f, 1.0f, 0.0f, position_.y,
            0.0f, 0.0f, 1.0f, position_.z,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        auto scale = Matrix4 {
            scale_.x, 0.0f, 0.0f, 0.0f,
            0.0f, scale_.y, 0.0f, 0.0f,
            0.0f, 0.0f, scale_.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        transform_ = translate * rotation_.GetMatrix() * scale;
        touched = false;
    }

    return transform_;
}

}