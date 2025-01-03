// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include <string>

namespace engine::math {

ENGINE_EXPORT const float pi = 3.1415926535897932384626433832795f;
ENGINE_EXPORT const float half_pi = 1.5707963267948966192313216916398f;
ENGINE_EXPORT const float two_pi = 6.2831853071795864769252867665590f;
ENGINE_EXPORT const float deg2rad = pi / 180.0f;
ENGINE_EXPORT const float rad2deg = 180.0f / pi;

[[nodiscard]] ENGINE_EXPORT inline auto DegToRad(const float degrees) {
    return degrees * deg2rad;
}

[[nodiscard]] ENGINE_EXPORT inline auto RadToDeg(const float radians) {
    return radians * rad2deg;
}

[[nodiscard]] ENGINE_EXPORT auto GenerateUUID() -> std::string;

}