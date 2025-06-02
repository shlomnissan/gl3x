/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/math/plane.hpp"

namespace gleam {

auto Plane::DistanceToPoint(const Vector3& point) const -> float {
    return Dot(normal, point) + distance;
}

auto Plane::DistanceToSphere(const Sphere& sphere) const -> float {
    return DistanceToPoint(sphere.center) - sphere.radius;
}

auto Plane::Normalize() -> void {
    const auto inverse_length = 1.0 / normal.Length();
    normal *= inverse_length;
    distance *= inverse_length;
}

}