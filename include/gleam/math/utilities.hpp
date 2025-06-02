/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <cmath>
#include <string>

namespace gleam::math {

constexpr float pi = 3.1415926535897932384626433832795f;
constexpr float half_pi = 1.5707963267948966192313216916398f;
constexpr float two_pi = 6.2831853071795864769252867665590f;
constexpr float epsilon = 1e-6f;

/**
 * @brief Converts degrees to radians.
 *
 * @param degrees Angle in degrees.
 * @return float Angle in radians.
 */
[[nodiscard]] constexpr auto DegToRad(const float degrees) {
    return degrees * (pi / 180.0f);
}

/**
 * @brief Converts radians to degrees.
 *
 * @param radians Angle in radians.
 * @return float Angle in degrees.
 */
[[nodiscard]] constexpr auto RadToDeg(const float radians) {
    return radians * (180.0f / pi);
}

/**
 * @brief Linearly interpolates between two values.
 *
 * @param a Start value.
 * @param b End value.
 * @param f Interpolation factor (0.0 to 1.0).
 * @return float Interpolated value.
 */
[[nodiscard]] constexpr auto Lerp(const float a, const float b, const float f) {
    return std::lerp(a, b, f);
}

/**
 * @brief Generates a UUID.
 *
 * @return std::string UUID.
 */
[[nodiscard]] GLEAM_EXPORT auto GenerateUUID() -> std::string;

}