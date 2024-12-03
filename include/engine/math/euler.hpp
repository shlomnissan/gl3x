// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"

namespace engine {

/**
 * @brief Represents Euler angles for 3D rotation.
 * Currently, the Euler class supports only the default rotation order of YXZ.
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
    explicit Euler(const Matrix4& m);

    /**
     * @brief Represents a set of Euler angles.
     *
     * This struct is used for designated initialization.
     */
    struct EulerAngles { float pitch; float yaw; float roll; };

    /**
     * @brief Constructor with initial values for Euler angles and rotation order.
     *
     * @param e The Euler angles to initialize the object with.
     */
    explicit Euler(const EulerAngles& e);

    /**
     * @brief Computes the rotation matrix based on the Euler angles and rotation order.
     *
     * @return The rotation matrix corresponding to the Euler angles and rotation order.
     */
    [[nodiscard]] auto GetMatrix() const -> Matrix4;

private:
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