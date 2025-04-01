// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include <string>

namespace engine::math {

constexpr float pi = 3.1415926535897932384626433832795f;
constexpr float half_pi = 1.5707963267948966192313216916398f;
constexpr float two_pi = 6.2831853071795864769252867665590f;
constexpr float deg2rad = pi / 180.0f;
constexpr float rad2deg = 180.0f / pi;
constexpr float epsilon = 1e-6f;

[[nodiscard]] constexpr auto DegToRad(const float degrees) {
    return degrees * deg2rad;
}

[[nodiscard]] constexpr auto RadToDeg(const float radians) {
    return radians * rad2deg;
}

[[nodiscard]] constexpr auto Lerp(const float a, const float b, const float f) {
    return a + (b - a) * f;
}

[[nodiscard]] ENGINE_EXPORT auto GenerateUUID() -> std::string;

}