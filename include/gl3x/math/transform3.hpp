/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/euler.hpp"
#include "gl3x/math/matrix4.hpp"
#include "gl3x/math/utilities.hpp"
#include "gl3x/math/vector3.hpp"

namespace gl3x {

/**
 * @brief A 3D transformation class supporting translation, scaling, and rotation.
 *
 * Internally manages position, scale, and rotation in Euler angles.
 * Lazily computes the final transformation matrix when accessed.
 *
 * @ingroup MathGroup
 */
class GL3X_EXPORT Transform3 {
public:
    /// @brief Indicates whether the transformation matrix needs to be recomputed.
    bool touched {true};

    /// @brief World-space translation.
    Vector3 position {0.0f};

    /// @brief Local scale.
    Vector3 scale {1.0f};

    /// @brief Euler rotation (pitch, yaw, roll).
    Euler rotation {};

    /**
     * @brief Constructs a Transform3 object with identity transform.
     */
    constexpr Transform3() = default;

    /**
     * @brief Applies a translation in local space.
     *
     * If rotation is non-zero, the translation is rotated accordingly.
     *
     * @param value Translation vector.
     */
    constexpr auto Translate(const Vector3& value) {
        position += rotation.IsEmpty() ? value : rotation.GetMatrix() * value;
        touched = true;
    }

    /**
     * @brief Applies a scale to the current scale.
     *
     * @param value Scale factors to apply.
     */
    constexpr auto Scale(const Vector3& value) {
        scale *= value;
        touched = true;
    }

    /**
     * @brief Applies a rotation around a specific axis.
     *
     * Only cardinal axes (X, Y, Z) are supported.
     *
     * @param axis Axis to rotate around (Right, Up, or Forward).
     * @param angle Rotation angle in radians.
     */
    constexpr auto Rotate(const Vector3& axis, float angle) {
        assert(axis == Vector3::Right() || axis == Vector3::Up() || axis == Vector3::Forward());
        if (axis == Vector3::Right()) {
            rotation.pitch += angle;
        }else if (axis == Vector3::Up()) {
            rotation.yaw += angle;
        } else if (axis == Vector3::Forward()) {
            rotation.roll += angle;
        }
        touched = true;
    }

    /**
     * @brief Sets the rotation such that the object looks at the given target.
     *
     * Computes the Euler rotation needed to look from `position` to `target`,
     * using the given world-up vector to determine orientation.
     *
     * @param position Position of the object.
     * @param target Target point to look at.
     * @param world_up World up direction.
     */
    constexpr auto LookAt(const Vector3& position, const Vector3& target, const Vector3& world_up) {
        auto forward = Normalize(target - position);
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

        rotation = Euler {{
            right.x, up.x, forward.x, 0.0f,
            right.y, up.y, forward.y, 0.0f,
            right.z, up.z, forward.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }};

        touched = true;
    }

    /**
     * @brief Sets the world position of the transform.
     *
     * @param position New position vector.
     */
    constexpr auto SetPosition(const Vector3& position) {
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
    constexpr auto SetScale(const Vector3& scale) {
        if (this->scale != scale) {
            this->scale = scale;
            touched = true;
        }
    }

    /**
     * @brief Sets the rotation of the transform.
     *
     * @param rotation New Euler rotation.
     */
    constexpr auto SetRotation(const Euler& rotation) {
        if (this->rotation != rotation) {
            this->rotation = rotation;
            touched = true;
        }
    }

    /**
     * @brief Returns the 4x4 transformation matrix.
     *
     * Lazily recomputes the matrix if any component has changed since last access.
     *
     * @return Final transformation matrix.
     */
    [[nodiscard]] constexpr auto Get() {
        if (touched) {
            const auto cos_p = math::Cos(rotation.pitch);
            const auto sin_p = math::Sin(rotation.pitch);
            const auto cos_y = math::Cos(rotation.yaw);
            const auto sin_y = math::Sin(rotation.yaw);
            const auto cos_r = math::Cos(rotation.roll);
            const auto sin_r = math::Sin(rotation.roll);

            transform_ = {
                scale.x * (cos_r * cos_y - sin_r * sin_p * sin_y),
                scale.y * (-sin_r * cos_p),
                scale.z * (cos_r * sin_y + sin_r * sin_p * cos_y),
                position.x,

                scale.x * (sin_r * cos_y + cos_r * sin_p * sin_y),
                scale.y * (cos_r * cos_p),
                scale.z * (sin_r * sin_y - cos_r * sin_p * cos_y),
                position.y,

                scale.x * (-cos_p * sin_y),
                scale.y * sin_p,
                scale.z * (cos_p * cos_y),
                position.z,

                0.0f, 0.0f, 0.0f, 1.0f
            };

            touched = false;
        }
        return transform_;
    }

private:
    /// @brief Cached transformation matrix.
    Matrix4 transform_ {1.0f};
};

}