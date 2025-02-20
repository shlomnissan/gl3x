// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/box3.hpp"

#include <algorithm>
#include <limits>

namespace engine {

Box3::Box3()
    : min_(std::numeric_limits<float>::max()),
      max_(std::numeric_limits<float>::lowest()) {}

Box3::Box3(const Vector3& v_min, const Vector3& v_max)
    : min_(v_min),
      max_(v_max) {}

auto Box3::ExpandWithPoint(const Vector3& p) -> void {
    if (p.x < min_.x) min_.x = p.x;
    if (p.y < min_.y) min_.y = p.y;
    if (p.z < min_.z) min_.z = p.z;
    if (p.x > max_.x) max_.x = p.x;
    if (p.y > max_.y) max_.y = p.y;
    if (p.z > max_.z) max_.z = p.z;
}

auto Box3::ExpandWithPoints(std::span<const Vector3> points) -> void {
    for (const auto& p : points) ExpandWithPoint(p);
}

}