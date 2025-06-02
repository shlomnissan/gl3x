/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/math/box3.hpp"

#include <algorithm>
#include <array>
#include <limits>

namespace gleam {

auto Box3::Reset() -> void {
    min = Vector3(std::numeric_limits<float>::max());
    max = Vector3(std::numeric_limits<float>::lowest());
}

auto Box3::ExpandWithPoint(const Vector3& p) -> void {
    if (p.x < min.x) min.x = p.x;
    if (p.y < min.y) min.y = p.y;
    if (p.z < min.z) min.z = p.z;
    if (p.x > max.x) max.x = p.x;
    if (p.y > max.y) max.y = p.y;
    if (p.z > max.z) max.z = p.z;
}

auto Box3::ApplyTransform(const Matrix4& transform) -> void {
    static std::array<Vector3, 8> points_ {};

    points_[0] = transform * Vector3 {min.x, min.y, min.z};
    points_[1] = transform * Vector3 {min.x, min.y, max.z};
    points_[2] = transform * Vector3 {min.x, max.y, min.z};
    points_[3] = transform * Vector3 {min.x, max.y, max.z};
    points_[4] = transform * Vector3 {max.x, min.y, min.z};
    points_[5] = transform * Vector3 {max.x, min.y, max.z};
    points_[6] = transform * Vector3 {max.x, max.y, min.z};
    points_[7] = transform * Vector3 {max.x, max.y, max.z};

    Reset();

    for (const auto& point : points_) ExpandWithPoint(point);
}

auto Box3::Translate(const Vector3& translation) -> void {
    min += translation;
    max += translation;
}

}