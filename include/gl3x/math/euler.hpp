/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/matrix4.hpp"
#include "gl3x/math/utilities.hpp"

namespace gl3x {

/**
 * @brief Represents 3D Euler angles with pitch, yaw, and roll components.
 *
 * `Euler` stores orientation using intrinsic Tait-Bryan angles in **YXZ order**, where:
 * - **yaw** is a rotation around the Y-axis,
 * - **pitch** is a rotation around the X-axis,
 * - **roll** is a rotation around the Z-axis.
 *
 * This class supports construction from individual angles or a transformation matrix,
 * and can convert back to a `Matrix4` representation for use in transformations.
 *
 * Note: Gimbal lock may occur when pitch approaches ±90°, limiting the reliability of angle reconstruction.
 *
 * @ingroup MathGroup
 */
class GL3X_EXPORT Euler  {
public:
    float pitch {0.0f}; ///< Rotation around the X-axis in radians.
    float yaw {0.0f}; ///< Rotation around the Y-axis in radians.
    float roll {0.0f}; ///< Rotation around the Z-axis in radians.

    /**
     * @brief Constructs an Euler angles object.
     */
    constexpr Euler() = default;

    /**
     * @brief Constructs an Euler angles object from pitch, yaw, and roll.
     *
     * @param pitch Rotation around the X-axis (in radians).
     * @param yaw Rotation around the Y-axis (in radians).
     * @param roll Rotation around the Z-axis (in radians).
     */
    constexpr Euler(float pitch, float yaw, float roll) :
        pitch(pitch),
        yaw(yaw),
        roll(roll) {}

    /**
     * @brief Constructs an Euler angles object from a transformation matrix.
     *
     * This constructor extracts pitch, yaw, and roll from a given matrix.
     * If gimbal lock is detected (when cos(pitch) is near zero), yaw is set to 0,
     * and roll is computed using an alternate strategy.
     *
     * @param m Input transformation matrix.
     */
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

    /**
     * @brief Converts the Euler angles into a 4×4 transformation matrix.
     *
     * The resulting matrix is constructed using the default YXZ rotation order.
     *
     * @return Transformation matrix representing the orientation.
     */
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

    /**
     * @brief Checks whether all angles are zero.
     *
     * @return true if pitch, yaw, and roll are all zero.
     */
    [[nodiscard]] constexpr auto IsEmpty() const {
        return pitch == 0.0f && yaw == 0.0f && roll == 0.0f;
    }

private:
    /// @brief Equality comparison operator.
    [[nodiscard]] friend constexpr auto operator==(const Euler& a, const Euler& b) -> bool = default;
};

}