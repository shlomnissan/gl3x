/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/sphere.hpp"
#include "gleam/math/vector3.hpp"

#include <cmath>

namespace gleam {

struct GLEAM_EXPORT Plane {
    Vector3 normal {Vector3::Up()};

    float distance {0.0f};

    Plane() = default;

    Plane(const Vector3& normal, float distance) :
        normal(normal),
        distance(distance) {}

    [[nodiscard]] auto DistanceToPoint(const Vector3& point) const {
        return Dot(normal, point) + distance;
    }

    [[nodiscard]] auto DistanceToSphere(const Sphere& sphere) const {
        return DistanceToPoint(sphere.center) - sphere.radius;
    }

    auto Normalize() {
        // TODO: Use fast inverse square root function to compute the length
        // and resolve failing tests due to precision loss
        const auto length = std::sqrt(Dot(normal, normal));
        const auto inverse_length = 1.0 / length;
        normal *= inverse_length;
        distance *= inverse_length;
    }
};

}