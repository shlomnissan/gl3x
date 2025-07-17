/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/sphere.hpp"
#include "gleam/math/utilities.hpp"
#include "gleam/math/vector3.hpp"

namespace gleam {

struct GLEAM_EXPORT Plane {
    Vector3 normal {Vector3::Up()};

    float distance {0.0f};

    constexpr Plane() = default;

    constexpr Plane(const Vector3& normal, float distance) :
        normal(normal),
        distance(distance) {}

    [[nodiscard]] constexpr auto DistanceToPoint(const Vector3& point) const {
        return Dot(normal, point) + distance;
    }

    [[nodiscard]] constexpr auto DistanceToSphere(const Sphere& sphere) const {
        return DistanceToPoint(sphere.center) - sphere.radius;
    }

    constexpr auto Normalize() {
        const auto inverse_length = math::InverseSqrt(Dot(normal, normal));
        normal *= inverse_length;
        distance *= inverse_length;
    }
};

}