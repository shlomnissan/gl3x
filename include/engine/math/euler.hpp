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
    /**
     * @brief Enum representing different rotation orders.
     */
    enum class ENGINE_EXPORT RotationOrder {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX
    };

    /// @brief The default rotation order, XYZ.
    static const auto default_order = RotationOrder::XYZ;

    /**
     * @brief Default constructor.
     *
     * Initializes the Euler angles to zero and uses the default rotation order.
     */
    Euler() = default;

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
     * @brief Computes the rotation matrix based on the Euler angles and rotation order.
     *
     * @return The rotation matrix corresponding to the Euler angles and rotation order.
     */
    [[nodiscard]] auto GetMatrix() const -> Matrix4;

private:
    /// @brief The pitch angle (rotation around X-axis), in radians.
    float pitch_ {0.0f};

    /// @brief The yaw angle (rotation around Y-axis), in radians.
    float yaw_ {0.0f};

    /// @brief The roll angle (rotation around Z-axis), in radians.
    float roll_ {0.0f};

    /// @brief The order in which rotations are applied.
    RotationOrder order_ = default_order;

    friend class Transform; ///< Allows `Transform` to access private members.

   /**
    * @brief Checks if two Euler objects are equal, component-wise.
    *
    * @param a The first Euler object to compare.
    * @param b The second Euler object to compare.
    * @return bool `true` if the Euler objcets are equal, `false` otherwise.
    */
    friend bool operator==(const Euler& a, const Euler& b) = default;
};

}