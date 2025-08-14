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

/**
 * @brief Axis-aligned bounding box defined by minimum and maximum corners.
 *
 * `Box3` represents a 3D volume bounded by two corners: `min` and `max`. It is
 * used for spatial queries, frustum culling, and bounding volume computations.
 * All operations assume the box is axis-aligned and defined in local space.
 *
 * @ingroup MathGroup
 */
struct GLEAM_EXPORT Box3 {
    /// @brief Minimum corner of the box.
    Vector3 min {std::numeric_limits<float>::max()};

    /// @brief Maximum corner of the box.
    Vector3 max {std::numeric_limits<float>::lowest()};


    /**
     * @brief Constructs a Box3 object.
     */
    constexpr Box3() = default;

    /**
     * @brief Constructs a Box3 object from minimum and maximum corners.
     *
     * @param v_min Minimum point.
     * @param v_max Maximum point.
     */
    constexpr Box3(const Vector3& v_min, const Vector3& v_max) :
        min(v_min),
        max(v_max) {}

    /**
     * @brief Returns the center point of the box.
     *
     * @return gleam::Vector3 Center of the box.
     */
    [[nodiscard]] constexpr auto Center() const { return (min + max) * 0.5f; }


    /**
     * @brief Checks whether the box is empty (invalid).
     *
     * A box is considered empty if any component of `min` exceeds the corresponding
     * component of `max`, which means it contains no volume.
     *
     * @return true if the box is empty, false otherwise.
     */
    [[nodiscard]] constexpr auto IsEmpty() const {
        return min.x > max.x || min.y > max.y || min.z > max.z;
    }

    /**
     * @brief Expands the box to include the given point.
     *
     * If the point lies outside the current box bounds, the box is enlarged to
     * include it.
     *
     * @param p Point to include in the box.
     */
    constexpr auto ExpandWithPoint(const Vector3& p) {
        if (p.x < min.x) min.x = p.x;
        if (p.y < min.y) min.y = p.y;
        if (p.z < min.z) min.z = p.z;
        if (p.x > max.x) max.x = p.x;
        if (p.y > max.y) max.y = p.y;
        if (p.z > max.z) max.z = p.z;
    }

    /**
     * @brief Resets the box to an empty state.
     *
     * This sets `min` and `max` to extreme values such that any point expanded into it
     * will become the new bounds.
     */
    constexpr auto Reset() {
        min = Vector3(std::numeric_limits<float>::max());
        max = Vector3(std::numeric_limits<float>::lowest());
    }

    /**
     * @brief Transforms the box by the given matrix.
     *
     * The resulting box is the axis-aligned bounding box that encloses the
     * transformed corners of the original box.
     *
     * @param transform 4x4 matrix to apply to the box.
     */
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

    /**
     * @brief Translates the box by a constant vector.
     *
     * @param translation Vector to add to both `min` and `max`.
     */
    constexpr auto Translate(const Vector3& translation) {
        min += translation;
        max += translation;
    }

    /**
     * @brief Expands this box to fully contain another box.
     *
     * @param other The box to merge into this one.
     */
    constexpr auto Union(const Box3& other) {
        min.Min(other.min);
        max.Max(other.max);
    }
};

}