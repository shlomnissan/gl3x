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

#include <cmath>

namespace gleam {

class GLEAM_EXPORT Transform2 {
public:
    bool touched {true};

    auto Translate(const Vector2& value) {
        position_ += value;
        touched = true;
    }

    auto Scale(const Vector2& value) {
        scale_ *= value;
        touched = true;
    }

    auto Rotate(float angle) {
        rotation_ += angle;
        touched = true;
    }

    auto SetPosition(const Vector2& position) {
        if (position_ != position) {
            position_ = position;
            touched = true;
        }
    }

    auto SetScale(const Vector2& scale) {
        if (scale_ != scale) {
            scale_ = scale;
            touched = true;
        }
    }

    auto SetRotation(float rotation) {
        if (rotation_ != rotation) {
            rotation_ = rotation;
            touched = true;
        }
    }

    auto SetCenter(const Vector2& center) {
        if (center_ != center) {
            center_ = center;
            touched = true;
        }
    }

    [[nodiscard]] auto GetPosition() const { return position_; }

    [[nodiscard]] auto GetScale() const { return scale_; }

    [[nodiscard]] auto GetRotation() const { return rotation_; }

    [[nodiscard]] auto GetCenter() const { return center_; }

    [[nodiscard]] auto Get() {
        if (touched) {
            touched = false;
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

private:
    Matrix3 transform_ {1.0f};

    Vector2 position_ {0.0f, 0.0f};

    Vector2 scale_ {1.0f, 1.0f};

    Vector2 center_ {0.0f, 0.0f};

    float rotation_ {0.0f};
};

}
