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

/**
 * @brief Represents a view frustum defined by six clipping planes.
 *
 * A `Frustum` is used for view frustum culling by the renderer, enabling efficient rejection of
 * geometry outside the visible camera volume. It is constructed from a view-projection
 * matrix and defines six planes: left, right, top, bottom, near, and far.
 *
 * This class supports containment and intersection tests with points, axis-aligned bounding boxes (AABB),
 * and bounding spheres. All tests assume the frustum planes face inward.
 *
 * @ingroup MathGroup
 */
struct GLEAM_EXPORT Frustum {
    /// @brief The six clipping planes of the frustum: left, right, top, bottom, near, far.
    std::array<Plane, 6> planes = {};

    /**
     * @brief Constructs a Frustum object.
     *
     * The resulting frustum will be uninitialized.
     */
    constexpr Frustum() = default;

    /**
     * @brief Updates the frustum using a new view-projection matrix.
     *
     * The planes are extracted directly from the matrix and normalized.
     *
     * @param projection View-projection matrix.
     */
    constexpr auto SetWithViewProjection(const Matrix4& projection) {
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

    /**
     * @brief Constructs a Frustum object from a view-projection matrix.
     *
     * @param projection View-projection matrix (typically `proj * view`).
     */
    explicit constexpr Frustum(const Matrix4& projection) {
        SetWithViewProjection(projection);
    }

    /**
     * @brief Checks whether a point is inside the frustum.
     *
     * @param point World-space position to test.
     * @return true if the point is inside or on all six planes.
     */
    [[nodiscard]] constexpr auto ContainsPoint(const Vector3& point) const {
        return std::ranges::all_of(planes, [&](const auto& plane) {
            return plane.DistanceToPoint(point) >= 0;
        });
    }

    /**
     * @brief Checks whether an axis-aligned bounding box intersects the frustum.
     *
     * Uses the "fast AABB frustum test" based on the frustum's plane normals.
     *
     * @param box Box to test against the frustum.
     * @return true if the box intersects or is fully inside the frustum.
     */
    [[nodiscard]] constexpr auto IntersectsWithBox3(const Box3& box) const {
        auto v = Vector3::Zero();
        return std::ranges::all_of(planes, [&](const auto& plane) {
            v.x = plane.normal.x > 0 ? box.max.x : box.min.x;
            v.y = plane.normal.y > 0 ? box.max.y : box.min.y;
            v.z = plane.normal.z > 0 ? box.max.z : box.min.z;
            return plane.DistanceToPoint(v) >= 0;
        });
    }

    /**
     * @brief Checks whether a sphere intersects the frustum.
     *
     * @param sphere Bounding sphere to test.
     * @return true if the sphere intersects or is fully inside the frustum.
     */
    [[nodiscard]] constexpr auto IntersectsWithSphere(const Sphere& sphere) const {
        return std::ranges::all_of(planes, [&](const auto& plane) {
            const auto distance = plane.DistanceToPoint(sphere.center);
            return distance >= -sphere.radius;
        });
    }
};

}