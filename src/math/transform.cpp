// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform.hpp"
#include "engine/math/transformations.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

auto Transform::Scale(float value) -> void {
    scale_ = scale_ * value;
    is_dirty_ = true;
}

auto Transform::Translate(const Vector3& axis, float distance) -> void {
    position_ = position_ + (axis * distance);
    is_dirty_ = true;
}

auto Transform::Rotate(const Vector3& axis, float angle) -> void {
    assert(axis == Vector3::Right() || axis == Vector3::Up() || axis == Vector3::Forward());
    if (axis == Vector3::Right()) {
        euler_.pitch_ += angle;
    }else if (axis == Vector3::Up()) {
        euler_.yaw_ += angle;
    } else if (axis == Vector3::Forward()) {
        euler_.roll_ += angle;
    }
    is_dirty_ = true;
}

auto Transform::ToMatrix() -> Matrix4 {
    if (is_dirty_) {
        transform_ = Matrix4 {1.0f};
        transform_ = translate(transform_, position_);
        transform_ = transform_ * euler_.GetMatrix();
        transform_ = scale(transform_, scale_);
        is_dirty_ = false;
    }
    return transform_;
}

}