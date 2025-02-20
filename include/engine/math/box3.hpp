// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/math/vector3.hpp"

#include <span>

namespace engine {

/**
 * @brief Represents an axis-aligned bounding box (AABB) in 3D space.
 */
class ENGINE_EXPORT Box3 {
public:
    /**
     * @brief Default constructor that initializes the box to
     * std::numeric_limits<float>::max() and std::numeric_limits<float>::lowest().
     */
    Box3();

    /**
     * @brief Constructs a box with the specified minimum and maximum points.
     *
     * @param v_min The minimum point of the box.
     * @param v_max The maximum point of the box.
     */
    Box3(const Vector3& v_min, const Vector3& v_max);

    /**
     * @brief Retrieves the minimum point of the box.
     *
     * @return The minimum point of the box as a Vector3.
     */
    auto Min() const { return min_; }

    /**
     * @brief Retrieves the maximum point of the box.
     *
     * @return The maximum point of the box as a Vector3.
     */
    auto Max() const { return max_; }

    /**
     * @brief Retrieves the center of the box.
     *
     * @return The center of the box as a Vector3.
     */
    auto Center() const { return (min_ + max_) * 0.5f; }

    /**
     * @brief Expands the box to include the specified point.
     *
     * @param p The point to include in the box.
     */
    auto ExpandWithPoint(const Vector3& p) -> void;

    /**
     * @brief Expands the box to include the specified points.
     *
     * @param points The points to include in the box.
     */
    auto ExpandWithPoints(std::span<const Vector3> points) -> void;

private:
    /// @brief The minimum point of the box.
    Vector3 min_;
    /// @brief The maximum point of the box.
    Vector3 max_;
};

}