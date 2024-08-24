// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform3d.hpp"
#include "engine/math/transformations.hpp"

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
    // TODO: replace with equality checks (e.g., axis == Vector3::X())
    if (axis.x == 1.0f && axis.y == 0.0f && axis.z == 0.0f) {
        euler_.pitch_ += angle;
    }
    if (axis.x == 0.0f && axis.y == 1.0f && axis.z == 0.0f) {
        euler_.yaw_ += angle;
    }
    if (axis.x == 0.0f && axis.y == 0.0f && axis.z == 1.0f) {
        euler_.roll_ += angle;
    }
    is_dirty_ = true;
}

auto Transform3D::ToMatrix() -> Matrix4 {
    if (is_dirty_) {
        transform_ = Matrix4 {1.0f};
        transform_ = translate(transform_, position_);
        transform_ = transform_ * euler_.GetMatrix(); // apply rotation
        transform_ = scale(transform_, scale_);
        is_dirty_ = false;
    }
    return transform_;
}

}