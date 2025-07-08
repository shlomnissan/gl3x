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

namespace gleam {

/**
 * @brief Represents a 3D transformation.
 */
class GLEAM_EXPORT Transform3 {
public:
    /// @brief Flag indicating if the transformation matrix was modified.
    bool touched {true};

    /**
     * @brief Update the position of the transformation.
     *
     * @param value The translation vector to apply.
     */
    auto Translate(const Vector3& value) -> void;

    /**
     * @brief Update the scale of the transformation.
     *
     * @param value The scaling vector to apply.
     */
    auto Scale(const Vector3& value) -> void;

    /**
     * @brief Update the rotation of the transformation.
     *
     * @param axis The axis to rotate around.
     * @param angle The angle to rotate by, in radians.
     */
    auto Rotate(const Vector3& axis, float angle) -> void;

    /**
     * @brief Sets the transformation to look at a target position.
     *
     * @param position The position of the object.
     * @param target The target position to look at.
     * @param world_up The up vector of the world.
     */
    auto LookAt(const Vector3& position, const Vector3& target, const Vector3& world_up) -> void;

    /**
     * @brief Sets the position of the transformation.
     *
     * @param position The position vector to set.
     */
    auto SetPosition(const Vector3& position) -> void;

    /**
     * @brief Sets the scale of the transformation.
     *
     * @param scale The scale vector to set.
     */
    auto SetScale(const Vector3& scale) -> void;

    /**
     * @brief Sets the rotation of the transformation.
     *
     * @param rotation The Euler angles to set.
     */
    auto SetRotation(const Euler& rotation) -> void;

    /**
     * @brief Retrieves the position of the transformation.
     *
     * @return The position vector.
     */
    [[nodiscard]] auto GetPosition() const { return position_; }

    /**
     * @brief Retrieves the scale of the transformation.
     *
     * @return The scale vector.
     */
    [[nodiscard]] auto GetScale() const { return scale_; };

    /**
     * @brief Retrieves the rotation of the transformation.
     *
     * @return The Euler angles.
     */
    [[nodiscard]] auto GetRotation() const { return rotation_; }

    /**
     * @brief Returns the transformation matrix.
     *
     * @return The transformation matrix representing the current scaling, translation, and rotation.
     */
    [[nodiscard]] auto Get() -> Matrix4;

private:
    /// @brief The transformation matrix, initialized to identity.
    Matrix4 transform_ {1.0f};

    /// @brief The position of the transformation.
    Vector3 position_ {0.0f};

    /// @brief The scale of the transformation.
    Vector3 scale_ {1.0f};

    /// @brief The rotation of the transformation.
    Euler rotation_ {};
};

}