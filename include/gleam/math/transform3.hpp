/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/euler.hpp"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/vector3.hpp"

#include <cmath>

namespace gleam {

class GLEAM_EXPORT Transform3 {
public:
    bool touched {true};

    auto Translate(const Vector3& value) {
        position_ += rotation_.IsEmpty() ? value : rotation_.GetMatrix() * value;
        touched = true;
    }

    auto Scale(const Vector3& value) {
        scale_ *= value;
        touched = true;
    }

    auto Rotate(const Vector3& axis, float angle) {
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

    auto LookAt(const Vector3& position, const Vector3& target, const Vector3& world_up) {
        auto forward = Normalize(position - target);
        if (forward == Vector3::Zero()) {
            // The position and target are the same,
            // so we can't determine a forward vector.
            forward = Vector3::Forward();
        }

        auto right = Cross(world_up, forward);
        if (right.Length() == 0.0f) {
            // If the right vector is zero, the forward vector
            // is parallel to the world up vector.
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

    auto SetPosition(const Vector3& position) {
        if (position_ != position) {
            position_ = position;
            touched = true;
        }
    }

    auto SetScale(const Vector3& scale) {
        if (scale_ != scale) {
            scale_ = scale;
            touched = true;
        }
    }

    auto SetRotation(const Euler& rotation) {
        if (rotation_ != rotation) {
            rotation_ = rotation;
            touched = true;
        }
    }

    [[nodiscard]] auto GetPosition() const { return position_; }

    [[nodiscard]] auto GetScale() const { return scale_; };

    [[nodiscard]] auto GetRotation() const { return rotation_; }

    [[nodiscard]] auto Get() {
        if (touched) {
            const auto cos_p = std::cos(rotation_.pitch);
            const auto sin_p = std::sin(rotation_.pitch);
            const auto cos_y = std::cos(rotation_.yaw);
            const auto sin_y = std::sin(rotation_.yaw);
            const auto cos_r = std::cos(rotation_.roll);
            const auto sin_r = std::sin(rotation_.roll);

            transform_ = {
                scale_.x * (cos_r * cos_y - sin_r * sin_p * sin_y),
                scale_.y * (-sin_r * cos_p),
                scale_.z * (cos_r * sin_y + sin_r * sin_p * cos_y),
                position_.x,

                scale_.x * (sin_r * cos_y + cos_r * sin_p * sin_y),
                scale_.y * (cos_r * cos_p),
                scale_.z * (sin_r * sin_y - cos_r * sin_p * cos_y),
                position_.y,

                scale_.x * (-cos_p * sin_y),
                scale_.y * sin_p,
                scale_.z * (cos_p * cos_y),
                position_.z,

                0.0f, 0.0f, 0.0f, 1.0f
            };

            touched = false;
        }
        return transform_;
    }

private:
    Matrix4 transform_ {1.0f};

    Vector3 position_ {0.0f};

    Vector3 scale_ {1.0f};

    Euler rotation_ {};
};

}