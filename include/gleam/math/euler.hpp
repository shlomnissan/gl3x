/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/matrix4.hpp"

namespace gleam {

// The default rotation order of YXZ.
class GLEAM_EXPORT Euler  {
public:
    float pitch {0.0f};
    float yaw {0.0f};
    float roll {0.0f};

    Euler() = default;

    Euler(float pitch, float yaw, float roll) :
        pitch(pitch),
        yaw(yaw),
        roll(roll) {}

    explicit Euler(const Matrix4& m) {
        pitch = std::asin(m[1].z);
        if (std::cos(pitch) > 1e-6) {
            yaw = std::atan2(-m[0].z, m[2].z);
            roll = std::atan2(-m[1].x, m[1].y);
        } else {
            // If cos(pitch) is close to zero, we have a gimble lock
            // and only one of the angles can be determined
            yaw = 0.0f;
            roll = std::atan2(m[0].y, m[0].x);
        }
    }

    [[nodiscard]] auto GetMatrix() const {
        const auto cos_p = std::cos(pitch);
        const auto sin_p = std::sin(pitch);
        const auto cos_y = std::cos(yaw);
        const auto sin_y = std::sin(yaw);
        const auto cos_r = std::cos(roll);
        const auto sin_r = std::sin(roll);

        return Matrix4 {
            cos_r * cos_y - sin_r * sin_p * sin_y, -sin_r * cos_p, cos_r * sin_y + sin_r * sin_p * cos_y, 0.0f,
            sin_r * cos_y + cos_r * sin_p * sin_y, cos_r * cos_p, sin_r * sin_y - cos_r * sin_p * cos_y, 0.0f,
            -cos_p * sin_y, sin_p, cos_p * cos_y, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    [[nodiscard]] auto IsEmpty() const {
        return pitch == 0.0f && yaw == 0.0f && roll == 0.0f;
    }

private:
   [[nodiscard]] friend auto operator==(const Euler& a, const Euler& b) -> bool = default;
};

}