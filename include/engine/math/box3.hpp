// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"

#include <limits>

namespace engine {

/**
 * @brief Represents an axis-aligned bounding box (AABB) in 3D space.
 */
class ENGINE_EXPORT Box3 {
public:
    /**
     * @brief Constructs a box with the specified minimum and maximum points.
     *
     * @param v_min The minimum point of the box.
     * @param v_max The maximum point of the box.
     */
    Box3(
        const Vector3& v_min = std::numeric_limits<float>::max(),
        const Vector3& v_max = std::numeric_limits<float>::lowest()
    ) : min_(v_min), max_(v_max) {}

    /**
     * @brief Retrieves the minimum point of the box.
     *
     * @return The minimum point of the box as a Vector3.
     */
    [[nodiscard]] auto Min() const { return min_; }

    /**
     * @brief Retrieves the maximum point of the box.
     *
     * @return The maximum point of the box as a Vector3.
     */
    [[nodiscard]] auto Max() const { return max_; }

    /**
     * @brief Retrieves the center of the box.
     *
     * @return The center of the box as a Vector3.
     */
    [[nodiscard]] auto Center() const { return (min_ + max_) * 0.5f; }

    /**
     * @brief Resets the box to std::numeric_limits<float>::max()
     * and std::numeric_limits<float>::lowest().
     */
    auto Reset() -> void;

    /**
     * @brief Checks if the box is empty.
     *
     * @return True if the box is empty, false otherwise.
     */
    [[nodiscard]] auto IsEmpty() const {
        return min_.x > max_.x || min_.y > max_.y || min_.z > max_.z;
    }

    /**
     * @brief Expands the box to include the specified point.
     *
     * @param p The point to include in the box.
     */
    auto ExpandWithPoint(const Vector3& p) -> void;

    /**
     * @brief Transforms the box by the specified matrix.
     *
     * @param transform The matrix to apply to the box.
     */
    auto ApplyTransform(const Matrix4& transform) -> void;

private:
    /// @brief The minimum point of the box.
    Vector3 min_;

    /// @brief The maximum point of the box.
    Vector3 max_;
};

}