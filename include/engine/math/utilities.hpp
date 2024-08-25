// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

namespace engine::math {

ENGINE_EXPORT const float pi = 3.1415926535897932384626433832795f;
ENGINE_EXPORT const float two_pi = 6.2831853071795864769252867665590f;
ENGINE_EXPORT const float deg2rad = pi / 180.0f;
ENGINE_EXPORT const float rad2deg = 180.0f / pi;

[[nodiscard]] ENGINE_EXPORT
auto DegToRad(const float degrees) -> float;

[[nodiscard]] ENGINE_EXPORT
auto RadToDeg(const float radians) -> float;

}