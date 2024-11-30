// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/vector4.hpp"

#include "engine/math/vector3.hpp"

#include <cmath>

namespace engine {

Vector4::Vector4() : Vector4(0.0) {}

Vector4::Vector4(float value) : Vector4(value, value, value, value) {}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4::Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

auto Vector4::Length() const -> float {
    return std::sqrt(Dot(*this, *this));
}

}