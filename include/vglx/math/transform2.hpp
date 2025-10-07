/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/math/matrix3.hpp"
#include "vglx/math/vector2.hpp"
#include "vglx/math/utilities.hpp"

namespace vglx {

/**
 * @brief A 2D transformation class supporting translation, scaling, and rotation.
 *
 * Internally manages position, scale, rotation, and center of transformation.
 * Lazily computes the final transformation matrix when accessed.
 *
 * @ingroup MathGroup
 */
class VGLX_EXPORT Transform2 {
public:
    /// @brief Indicates whether the transformation matrix needs to be recomputed.
    bool touched {true};

    /// @brief World-space translation.
    Vector2 position {0.0f, 0.0f};

    /// @brief Local scale.
    Vector2 scale {1.0f, 1.0f};

    /// @brief Pivot for rotation and scaling.
    Vector2 center {0.0f, 0.0f};

    /// @brief Rotation angle in radians.
    float rotation {0.0f};

    /**
     * @brief Constructs a Transform2 object with identity transform.
     */
    constexpr Transform2() = default;

    /**
     * @brief Applies a translation in local space.
     *
     * If rotation is non-zero, the translation is rotated accordingly.
     *
     * @param value Translation vector.
     */
    constexpr auto Translate(const Vector2& value) {
        const float s = math::Sin(rotation);
        const float c = math::Cos(rotation);
        const Vector2 rotated_value = {
            value.x * c - value.y * s,
            value.x * s + value.y * c
        };
        position += rotated_value;
        touched = true;
    }

    /**
     * @brief Applies a scale to the current scale.
     *
     * @param value Scale factors to apply.
     */
    constexpr auto Scale(const Vector2& value) {
        scale *= value;
        touched = true;
    }

    /**
     * @brief Applies a rotation delta to the current rotation.
     *
     * @param angle Rotation angle in radians.
     */
    constexpr auto Rotate(float angle) {
        rotation += angle;
        touched = true;
    }

    /**
     * @brief Sets the world position of the transform.
     *
     * @param position New position vector.
     */
    constexpr auto SetPosition(const Vector2& position) {
        if (this->position != position) {
            this->position = position;
            touched = true;
        }
    }

    /**
     * @brief Sets the local scale of the transform.
     *
     * @param scale New scale vector.
     */
    constexpr auto SetScale(const Vector2& scale) {
        if (this->scale != scale) {
            this->scale = scale;
            touched = true;
        }
    }

    /**
     * @brief Sets the rotation angle of the transform.
     *
     * @param rotation Rotation angle in radians.
     */
    constexpr auto SetRotation(float rotation) {
        if (this->rotation != rotation) {
            this->rotation = rotation;
            touched = true;
        }
    }

    /**
     * @brief Sets the pivot point for rotation and scaling.
     *
     * @param center Pivot point in local space.
     */
    constexpr auto SetCenter(const Vector2& center) {
        if (this->center !=center) {
            this->center = center;
            touched = true;
        }
    }

    /**
     * @brief Returns the 3x3 transformation matrix.
     *
     * Lazily recomputes the matrix if any component has changed since last access.
     *
     * @return Final transformation matrix.
     */
    [[nodiscard]] constexpr auto Get() {
        if (touched) {
            touched = false;
            const float rc = math::Cos(rotation);
            const float rs = math::Sin(rotation);
            const float tx = -scale.x * (rc * center.x - rs * center.y) + center.x + position.x;
            const float ty = -scale.y * (rs * center.x + rc * center.y) + center.y + position.y;
            transform_ = {
                scale.x * rc, -scale.x * rs, tx,
                scale.y * rs,  scale.y * rc, ty,
                0.0f, 0.0f, 1.0f
            };
        }
        return transform_;
    }

private:
    /// @brief Cached transformation matrix.
    Matrix3 transform_ {1.0f};
};

}
