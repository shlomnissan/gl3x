/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/matrix4.hpp"
#include "gleam/math/utilities.hpp"

namespace gleam {

// The default rotation order of YXZ.
class GLEAM_EXPORT Euler  {
public:
    float pitch {0.0f};
    float yaw {0.0f};
    float roll {0.0f};

    constexpr Euler() = default;

    constexpr Euler(float pitch, float yaw, float roll) :
        pitch(pitch),
        yaw(yaw),
        roll(roll) {}

    explicit constexpr Euler(const Matrix4& m) {
        pitch = math::Asin(m[1].z);
        if (math::Cos(pitch) > 1e-6) {
            yaw = math::Atan2(-m[0].z, m[2].z);
            roll = math::Atan2(-m[1].x, m[1].y);
        } else {
            // If cos(pitch) is close to zero, we have a gimble lock
            // and only one of the angles can be determined
            yaw = 0.0f;
            roll = math::Atan2(m[0].y, m[0].x);
        }
    }

    [[nodiscard]] constexpr auto GetMatrix() const {
        const auto cos_p = math::Cos(pitch);
        const auto sin_p = math::Sin(pitch);
        const auto cos_y = math::Cos(yaw);
        const auto sin_y = math::Sin(yaw);
        const auto cos_r = math::Cos(roll);
        const auto sin_r = math::Sin(roll);

        return Matrix4 {
            cos_r * cos_y - sin_r * sin_p * sin_y, -sin_r * cos_p, cos_r * sin_y + sin_r * sin_p * cos_y, 0.0f,
            sin_r * cos_y + cos_r * sin_p * sin_y, cos_r * cos_p, sin_r * sin_y - cos_r * sin_p * cos_y, 0.0f,
            -cos_p * sin_y, sin_p, cos_p * cos_y, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    [[nodiscard]] constexpr auto IsEmpty() const {
        return pitch == 0.0f && yaw == 0.0f && roll == 0.0f;
    }

private:
   [[nodiscard]] friend constexpr auto operator==(const Euler& a, const Euler& b) -> bool = default;
};

}