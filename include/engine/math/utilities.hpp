// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <string>

namespace engine::math {

ENGINE_EXPORT constexpr float pi = 3.1415926535897932384626433832795f;
ENGINE_EXPORT constexpr float two_pi = 6.2831853071795864769252867665590f;
ENGINE_EXPORT constexpr float deg2rad = pi / 180.0f;
ENGINE_EXPORT constexpr float rad2deg = 180.0f / pi;

[[nodiscard]] ENGINE_EXPORT
constexpr auto DegToRad(const float degrees) {
    return degrees * deg2rad;
}

[[nodiscard]] ENGINE_EXPORT
constexpr auto RadToDeg(const float radians) {
    return radians * rad2deg;
}

[[nodiscard]] ENGINE_EXPORT
auto GenerateUUID() -> std::string;

}