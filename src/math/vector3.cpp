// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/vector3.hpp>

#include <cmath>

using namespace engine;

Vector3::Vector3() : Vector3(0.0) {}

Vector3::Vector3(float value) : Vector3(value, value, value) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

auto Vector3::length() const -> float {
    return std::sqrt(dot(*this, *this));
}