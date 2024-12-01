// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"

namespace engine {

/**
 * @brief Represents Euler angles for 3D rotation.
 */
class ENGINE_EXPORT Euler  {
public:
    /// @brief The pitch angle (rotation around X-axis), in radians.
    float pitch {0.0f};
    /// @brief The yaw angle (rotation around Y-axis), in radians.
    float yaw {0.0f};
    /// @brief The roll angle (rotation around Z-axis), in radians.
    float roll {0.0f};

    /**
     * @brief Enum representing different rotation orders.
     */
    enum class RotationOrder {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX
    };

    /// @brief The default rotation order, XYZ.
    static const auto default_order = RotationOrder::YXZ;

    /**
     * @brief Default constructor.
     *
     * Initializes the Euler angles to zero and uses the default rotation order.
     */
    Euler() = default;

    /**
     * @brief Constructor with initial values for Euler angles and rotation order.
     *
     * @param m The rotation matrix to extract Euler angles from.
     * @param order The rotation order to be used, defaults to `default_order`.
     */
    Euler(const Matrix4& m, RotationOrder order = default_order);

    /**
     * @brief Constructor with initial values for Euler angles and rotation order.
     *
     * @param pitch The initial pitch angle (rotation around X-axis), in radians.
     * @param yaw The initial yaw angle (rotation around Y-axis), in radians.
     * @param roll The initial roll angle (rotation around Z-axis), in radians.
     * @param order The rotation order to be used, defaults to `default_order`.
     */
    Euler(float pitch, float yaw, float roll, RotationOrder order = default_order);

    /**
     * @brief Sets the rotation order for the Euler angles.
     *
     * @param order The rotation order to set.
     */
    auto SetRotationOrder(RotationOrder order) { order_ = order; }

    /**
    * @brief Rotates a matrix by a given angle around a specified axis.
    *
    * @param m The matrix to be rotated.
    * @param angle The angle of rotation in radians.
    * @param v The axis of rotation.
    * @return Matrix4 The resulting matrix after rotation.
    */
    auto Rotate(const Matrix4& m, float angle, const Vector3& v) const -> Matrix4;

    /**
     * @brief Computes the rotation matrix based on the Euler angles and rotation order.
     *
     * @return The rotation matrix corresponding to the Euler angles and rotation order.
     */
    [[nodiscard]] auto GetMatrix() const -> Matrix4;

private:
    /// @brief The order in which rotations are applied.
    RotationOrder order_ = default_order;

   /**
     * @brief Checks if two Euler objects are equal, component-wise.
     *
     * @param a The first Euler object to compare.
     * @param b The second Euler object to compare.
     * @return bool `true` if the Euler objcets are equal, `false` otherwise.
     */
   [[nodiscard]] friend bool operator==(const Euler& a, const Euler& b) = default;
};

}