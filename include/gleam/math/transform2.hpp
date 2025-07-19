/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/matrix3.hpp"
#include "gleam/math/vector2.hpp"
#include "gleam/math/utilities.hpp"

namespace gleam {

class GLEAM_EXPORT Transform2 {
public:
    bool touched {true};

    constexpr Transform2() = default;

    constexpr auto Translate(const Vector2& value) {
        const float s = math::Sin(rotation_);
        const float c = math::Cos(rotation_);
        const Vector2 rotated_value = {
            value.x * c - value.y * s,
            value.x * s + value.y * c
        };
        position_ += rotated_value;
        touched = true;
    }

    constexpr auto Scale(const Vector2& value) {
        scale_ *= value;
        touched = true;
    }

    constexpr auto Rotate(float angle) {
        rotation_ += angle;
        touched = true;
    }

    constexpr auto SetPosition(const Vector2& position) {
        if (position_ != position) {
            position_ = position;
            touched = true;
        }
    }

    constexpr auto SetScale(const Vector2& scale) {
        if (scale_ != scale) {
            scale_ = scale;
            touched = true;
        }
    }

    constexpr auto SetRotation(float rotation) {
        if (rotation_ != rotation) {
            rotation_ = rotation;
            touched = true;
        }
    }

    constexpr auto SetCenter(const Vector2& center) {
        if (center_ != center) {
            center_ = center;
            touched = true;
        }
    }

    [[nodiscard]] constexpr auto GetPosition() const { return position_; }

    [[nodiscard]] constexpr auto GetScale() const { return scale_; }

    [[nodiscard]] constexpr auto GetRotation() const { return rotation_; }

    [[nodiscard]] constexpr auto GetCenter() const { return center_; }

    [[nodiscard]] constexpr auto Get() {
        if (touched) {
            touched = false;
            const float rc = math::Cos(rotation_);
            const float rs = math::Sin(rotation_);
            const float tx = -scale_.x * (rc * center_.x - rs * center_.y) + center_.x + position_.x;
            const float ty = -scale_.y * (rs * center_.x + rc * center_.y) + center_.y + position_.y;
            transform_ = {
                scale_.x * rc, -scale_.x * rs, tx,
                scale_.y * rs,  scale_.y * rc, ty,
                0.0f, 0.0f, 1.0f
            };
        }
        return transform_;
    }

private:
    Matrix3 transform_ {1.0f};

    Vector2 position_ {0.0f, 0.0f};

    Vector2 scale_ {1.0f, 1.0f};

    Vector2 center_ {0.0f, 0.0f};

    float rotation_ {0.0f};
};

}
