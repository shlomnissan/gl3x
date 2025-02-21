// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/box3.hpp"

#include "engine/math/matrix3.hpp"

#include <algorithm>
#include <array>
#include <limits>

namespace engine {

auto Box3::Reset() -> void {
    min_ = Vector3(std::numeric_limits<float>::max());
    max_ = Vector3(std::numeric_limits<float>::lowest());
}

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

auto Box3::ApplyTransform(const Matrix4& transform) -> void {
    static std::array<Vector3, 8> points_ {};

    points_[0] = transform * Vector3 {min_.x, min_.y, min_.z};
    points_[1] = transform * Vector3 {min_.x, min_.y, max_.z};
    points_[2] = transform * Vector3 {min_.x, max_.y, min_.z};
    points_[3] = transform * Vector3 {min_.x, max_.y, max_.z};
    points_[4] = transform * Vector3 {max_.x, min_.y, min_.z};
    points_[5] = transform * Vector3 {max_.x, min_.y, max_.z};
    points_[6] = transform * Vector3 {max_.x, max_.y, min_.z};
    points_[7] = transform * Vector3 {max_.x, max_.y, max_.z};

    Reset();

    ExpandWithPoints(points_);
}

}