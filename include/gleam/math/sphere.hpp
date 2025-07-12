/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/matrix4.hpp"
#include "gleam/math/vector3.hpp"

#include <algorithm>
#include <cmath>

namespace gleam {

struct GLEAM_EXPORT Sphere {
    Vector3 center {Vector3::Zero()};

    float radius {-1.0f};

    Sphere() = default;

    Sphere(const Vector3 center, float radius) :
        center(center),
        radius(radius) {}

    [[nodiscard]] auto Radius() const { return radius; }

    auto Reset() {
        center = Vector3::Zero();
        radius = -1.0f;
    }

    [[nodiscard]] auto IsEmpty() const {
        return radius < 0.0f;
    }

    auto ExpandWithPoint(const Vector3& p) {
        // Handle the case where the sphere is empty (invalid).
        // In this case, the sphere is centered at the point and has a radius of 0.
        if (IsEmpty()) {
            center = p;
            radius = 0.0f;
            return;
        }

        const auto delta = p - center;
        const auto length_sqr = delta.LengthSquared();
        if (length_sqr > radius * radius) {
            const auto length = std::sqrt(length_sqr);
            // Move the center halfway towards the new pointm and expand the radius
            // by half the distance to the new point.
            const auto half_way = (length - radius) * 0.5f;
            center += delta * (half_way / length);
            radius += half_way;
        }
    }

    auto ApplyTransform(const Matrix4& transform) {
        center = transform * center;
        auto& t0 = transform[0];
        auto& t1 = transform[1];
        auto& t2 = transform[2];

        radius *= std::sqrt(std::max({
            Vector3 {t0.x, t0.y, t0.z}.LengthSquared(),
            Vector3 {t1.x, t1.y, t1.z}.LengthSquared(),
            Vector3 {t2.x, t2.y, t2.z}.LengthSquared(),
        }));
    }

    auto Translate(const Vector3& translation) {
        center += translation;
    }
};

}