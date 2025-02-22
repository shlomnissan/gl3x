// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/sphere.hpp"

#include <algorithm>
#include <cmath>

namespace engine {

auto Sphere::Reset() -> void {
    center_ = Vector3::Zero();
    radius_ = -1.0f;
}

auto Sphere::ExpandWithPoint(const Vector3 &p) -> void {
    // Handle the case where the sphere is empty (invalid).
    // In this case, the sphere is centered at the point and has a radius of 0.
    if (IsEmpty()) {
        center_ = p;
        radius_ = 0.0f;
        return;
    }

    const auto delta = p - center_;
    const auto length_sqr = delta.LengthSquared();
    if (length_sqr > radius_ * radius_) {
        const auto length = std::sqrt(length_sqr);
        // Move the center halfway towards the new pointm and expand the radius
        // by half the distance to the new point.
        const auto half_way = (length - radius_) * 0.5f;
        center_ += delta * (half_way / length);
        radius_ += half_way;
    }
}

auto Sphere::ApplyTransform(const Matrix4 &transform) -> void {
    center_ = transform * center_;
    radius_ *= std::sqrt(std::max({
        Vector3 {transform[0]}.LengthSquared(),
        Vector3 {transform[1]}.LengthSquared(),
        Vector3 {transform[2]}.LengthSquared()
    }));
}

}