// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/math/vector3.hpp"

#include "gleam/math/vector4.hpp"

#include <cmath>

namespace engine {

Vector3::Vector3() : Vector3(0.0f) {}

Vector3::Vector3(float value) : Vector3(value, value, value) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(const Vector4& v) : x(v.x), y(v.y), z(v.z) {}

auto Vector3::Length() const -> float {
    return std::sqrt(Dot(*this, *this));
}

auto Vector3::LengthSquared() const -> float {
    return Dot(*this, *this);
}

}