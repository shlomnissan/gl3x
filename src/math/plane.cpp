// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/plane.hpp"

namespace engine {

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