// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/math/transform2.hpp"

#include <cmath>

namespace gleam {

auto Transform2::Translate(const Vector2& value) -> void {
    position_ += value;
    touched_ = true;
}

auto Transform2::Scale(const Vector2& value) -> void {
    scale_ *= value;
    touched_ = true;
}

auto Transform2::Rotate(float angle) -> void {
    rotation_ += angle;
    touched_ = true;
}

auto Transform2::SetPosition(const Vector2& position) -> void {
    if (position_ != position) {
        position_ = position;
        touched_ = true;
    }
}

auto Transform2::SetScale(const Vector2& scale) -> void {
    if (scale_ != scale) {
        scale_ = scale;
        touched_ = true;
    }
}

auto Transform2::SetRotation(float rotation) -> void {
    if (rotation_ != rotation) {
        rotation_ = rotation;
        touched_ = true;
    }
}

auto Transform2::SetCenter(const Vector2& center) -> void {
    if (center_ != center) {
        center_ = center;
        touched_ = true;
    }
}

auto Transform2::Get() -> Matrix3 {
    if (touched_) {
        touched_ = false;
        // This transform is currently used for UV transformations.
        // 2D screen space transformations will require minor adjustments.
        const auto rc = std::cos(rotation_);
        const auto rs = std::sin(rotation_);
        const auto ts = -scale_.x * (rc * center_.x + rs * center_.y) + center_.x + position_.x;
        const auto ty = -scale_.y * (-rs * center_.x + rc * center_.y) + center_.y + position_.y;
        transform_ = {
            scale_.x * rc, scale_.x * rs, ts,
            -scale_.y * rs, scale_.y * rc, ty,
            0.0f, 0.0f, 1.0f
        };
    }
    return transform_;
}

}