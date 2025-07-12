/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/box3.hpp"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/sphere.hpp"
#include "gleam/math/plane.hpp"

#include <algorithm>
#include <array>

namespace gleam {

struct GLEAM_EXPORT Frustum {
    std::array<Plane, 6> planes = {};

    Frustum() = default;

    auto SetWithViewProjection(const Matrix4& projection) {
        planes[0] = Plane {{
            projection(3, 0) + projection(0, 0),
            projection(3, 1) + projection(0, 1),
            projection(3, 2) + projection(0, 2)
        }, projection(3, 3) + projection(0, 3)};

        planes[1] = Plane {{
            projection(3, 0) - projection(0, 0),
            projection(3, 1) - projection(0, 1),
            projection(3, 2) - projection(0, 2)
        }, projection(3, 3) - projection(0, 3)};

        planes[2] = Plane {{
            projection(3, 0) + projection(1, 0),
            projection(3, 1) + projection(1, 1),
            projection(3, 2) + projection(1, 2)
        }, projection(3, 3) + projection(1, 3)};

        planes[3] = Plane {{
            projection(3, 0) - projection(1, 0),
            projection(3, 1) - projection(1, 1),
            projection(3, 2) - projection(1, 2)
        }, projection(3, 3) - projection(1, 3)};

        planes[4] = Plane {{
            projection(3, 0) + projection(2, 0),
            projection(3, 1) + projection(2, 1),
            projection(3, 2) + projection(2, 2)
        }, projection(3, 3) + projection(2, 3)};

        planes[5] = Plane {{
            projection(3, 0) - projection(2, 0),
            projection(3, 1) - projection(2, 1),
            projection(3, 2) - projection(2, 2)
        }, projection(3, 3) - projection(2, 3)};

        for (auto& p : planes) p.Normalize();
    }

    explicit Frustum(const Matrix4& projection) {
        SetWithViewProjection(projection);
    }

    [[nodiscard]] auto ContainsPoint(const Vector3& point) const {
        return std::ranges::all_of(planes, [&](const auto& plane) {
            return plane.DistanceToPoint(point) >= 0;
        });
    }

    [[nodiscard]] auto IntersectsWithBox3(const Box3& box) const {
        auto v = Vector3::Zero();
        return std::ranges::all_of(planes, [&](const auto& plane) {
            v.x = plane.normal.x > 0 ? box.max.x : box.min.x;
            v.y = plane.normal.y > 0 ? box.max.y : box.min.y;
            v.z = plane.normal.z > 0 ? box.max.z : box.min.z;
            return plane.DistanceToPoint(v) >= 0;
        });
    }

    [[nodiscard]] auto IntersectsWithSphere(const Sphere& sphere) const {
        return std::ranges::all_of(planes, [&](const auto& plane) {
            const auto distance = plane.DistanceToPoint(sphere.center);
            return distance >= -sphere.radius;
        });
    }
};

}