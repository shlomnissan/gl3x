// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/euler.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

/**
 * @brief Represents a 3D transformation.
 */
class ENGINE_EXPORT Transform {
public:
    /**
     * @brief Applies a uniform scaling transformation.
     *
     * @param value The scaling factor to apply.
     */
    auto Scale(float value) -> void;

    /**
     * @brief Applies a scaling transformation.
     *
     * @param value The scaling vector to apply.
     */
    auto Scale(const Vector3& value) -> void;

    /**
     * @brief Applies a rotation transformation around a specified axis.
     *
     * @param axis The axis to rotate around. Must be (1,0,0), (0,1,0), or (0,0,1).
     * @param angle The angle to rotate by, in radians.
     */
    auto Rotate(const Vector3& axis, float angle) -> void;

    /**
     * @brief Applies a translation transformation.
     *
     * @param value The translation vector to apply.
     */
    auto Translate(const Vector3& value) -> void;

    /**
     * @brief Computes the current transformation matrix.
     *
     * This method calculates and returns the transformation matrix, If the transformation
     * is marked as dirty, it will be recalculated before being returned.
     *
     * @return The transformation matrix representing the current scaling and translation.
     */
    [[nodiscard]] auto ToMatrix() -> Matrix4;

    /**
     * @brief Checks if the transformation matrix is dirty.
     *
     * @return True if the transformation matrix needs to be recalculated, false otherwise.
     */
    [[nodiscard]] auto IsDirty() const { return is_dirty_; }

    /**
     * @brief Retrieves the position vector.
     *
     * @return The position vector.
     */
    [[nodiscard]] auto Position() const { return position_; }

    /**
     * @brief Retrieves the scale vector.
     *
     * @return The scale vector.
     */
    [[nodiscard]] auto Scale() const { return scale_; }

    /**
     * @brief Retrieves the rotation vector.
     *
     * @return The rotation vector.
     */
    [[nodiscard]] auto Rotation() const { return euler_; }

private:
    /// @brief Flag indicating if the transformation matrix needs to be recalculated.
    bool is_dirty_ {true};

    /// @brief The transformation matrix, initialized to identity.
    Matrix4 transform_ {1.0f};

    /// @brief The position vector representing translation.
    Vector3 position_ {0.0f};

    /// @brief The scale vector representing scaling.
    Vector3 scale_ {1.0f};

    /// @brief The Euler object representing rotations.
    Euler euler_ {};

   /**
     * @brief Checks if two Transform objects are equal, component-wise.
     *
     * @param a The first Transform object to compare.
     * @param b The second Transform object to compare.
     * @return bool `true` if the Euler objcets are equal, `false` otherwise.
     */
    [[nodiscard]]
    friend bool operator==(const Transform& a, const Transform& b) = default;
};

}