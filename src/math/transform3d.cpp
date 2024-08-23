// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/transform3d.hpp"
#include "engine/math/transformations.hpp"

namespace engine {

auto Transform3D::Scale(float value) -> void {
    scale_ = scale_ * value;
    is_dirty_ = true;
}

auto Transform3D::Translate(const Vector3& axis, float value) -> void {
    position_ = position_ + (axis * value);
    is_dirty_ = true;
}

auto Transform3D::Get() -> Matrix4 {
    if (is_dirty_) {
        transform_ = Matrix4 {1.0f};
        transform_ = translate(transform_, position_);
        transform_ = scale(transform_, scale_);
        is_dirty_ = false;
    }
    return transform_;
}

}