/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/math/sphere.hpp"

#include <algorithm>
#include <cmath>

namespace gleam {

auto Sphere::Reset() -> void {
    center = Vector3::Zero();
    radius = -1.0f;
}

auto Sphere::ExpandWithPoint(const Vector3 &p) -> void {
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

auto Sphere::ApplyTransform(const Matrix4 &transform) -> void {
    center = transform * center;
    radius *= std::sqrt(std::max({
        Vector3 {transform[0]}.LengthSquared(),
        Vector3 {transform[1]}.LengthSquared(),
        Vector3 {transform[2]}.LengthSquared()
    }));
}

auto Sphere::Translate(const Vector3 &translation) -> void {
    center += translation;
}

}