// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform3d.hpp"
#include "engine/math/transformations.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

auto Transform3D::Scale(float value) -> void {
    scale_ = scale_ * value;
    is_dirty_ = true;
}

auto Transform3D::Translate(const Vector3& axis, float distance) -> void {
    position_ = position_ + (axis * distance);
    is_dirty_ = true;
}

auto Transform3D::Rotate(const Vector3& axis, float angle) -> void {
    assert(axis == Vector3::X() || axis == Vector3::Y() || axis == Vector3::Z());
    if (axis == Vector3::X()) {
        euler_.pitch_ += angle;
    }else if (axis == Vector3::Y()) {
        euler_.yaw_ += angle;
    } else if (axis == Vector3::Z()) {
        euler_.roll_ += angle;
    }
    is_dirty_ = true;
}

auto Transform3D::ToMatrix() -> Matrix4 {
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