/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/math/vector4.hpp"

#include "gleam/math/vector3.hpp"

#include <cmath>

namespace gleam {

Vector4::Vector4(float value) : Vector4(value, value, value, value) {}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4::Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

auto Vector4::Length() const -> float {
    return std::sqrt(Dot(*this, *this));
}

auto Vector4::LengthSquared() const -> float {
    return Dot(*this, *this);
}

}