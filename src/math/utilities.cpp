// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/utilities.hpp"

namespace engine::math {

/**
 * @brief Converts degrees to radians.
 * 
 * @param degrees Angle in degrees.
 * @return Angle in radians.
 */
auto DegToRad(const float degrees) -> float {
    return degrees * deg2rad;
}

/**
 * @brief Converts radians to degrees.
 * 
 * @param radians Angle in radians.
 * @return Angle in degrees.
 */
auto RadToDeg(const float radians) -> float {
    return radians * rad2deg;
}

}