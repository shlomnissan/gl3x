// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/plane.hpp"

namespace engine {

auto Plane::DistanceToPoint(const Vector3& point) const -> float {
    return Dot(engine::Normalize(normal_), point) - distance_;
}

auto Plane::DistanceToSphere(const Sphere& sphere) const -> float {
    return DistanceToPoint(sphere.Center()) - sphere.Radius();
}

auto Plane::Normalize() -> void {
    const auto inverse_length = 1.0 / normal_.Length();
    normal_ *= inverse_length;
    distance_ *= inverse_length;
}

}