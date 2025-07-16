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

#include <array>
#include <limits>

namespace gleam {

struct GLEAM_EXPORT Box3 {
    Vector3 min {std::numeric_limits<float>::max()};
    Vector3 max {std::numeric_limits<float>::lowest()};

    constexpr Box3() = default;

    constexpr Box3(const Vector3& v_min, const Vector3& v_max) :
        min(v_min),
        max(v_max) {}

    [[nodiscard]] constexpr auto Center() const { return (min + max) * 0.5f; }


    [[nodiscard]] constexpr auto IsEmpty() const {
        return min.x > max.x || min.y > max.y || min.z > max.z;
    }

    constexpr auto ExpandWithPoint(const Vector3& p) {
        if (p.x < min.x) min.x = p.x;
        if (p.y < min.y) min.y = p.y;
        if (p.z < min.z) min.z = p.z;
        if (p.x > max.x) max.x = p.x;
        if (p.y > max.y) max.y = p.y;
        if (p.z > max.z) max.z = p.z;
    }

    constexpr auto Reset() {
        min = Vector3(std::numeric_limits<float>::max());
        max = Vector3(std::numeric_limits<float>::lowest());
    }

    constexpr auto ApplyTransform(const Matrix4& transform) {
        std::array<Vector3, 8> points_ {};

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

    constexpr auto Translate(const Vector3& translation) {
        min += translation;
        max += translation;
    }
};

}