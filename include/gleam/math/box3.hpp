// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/vector3.hpp"

#include <limits>

namespace engine {

/**
 * @brief Represents an axis-aligned bounding box (AABB) in 3D space.
 */
struct GLEAM_EXPORT Box3 {
    /// @brief The minimum point of the box.
    Vector3 min {std::numeric_limits<float>::max()};

    /// @brief The maximum point of the box.
    Vector3 max {std::numeric_limits<float>::lowest()};

    /**
     * @brief Constructs a new Box3 object.
     */
    Box3() = default;

    /**
     * @brief Constructs a box with the specified minimum and maximum points.
     *
     * @param v_min The minimum point of the box.
     * @param v_max The maximum point of the box.
     */
    Box3(const Vector3& v_min, const Vector3& v_max)
      : min(v_min), max(v_max) {}

    /**
     * @brief Retrieves the center of the box.
     *
     * @return The center of the box as a Vector3.
     */
    [[nodiscard]] auto Center() const { return (min + max) * 0.5f; }

    /**
     * @brief Resets the box to its empty state.
     */
    auto Reset() -> void;

    /**
     * @brief Checks if the box is empty.
     *
     * @return True if the box is empty, false otherwise.
     */
    [[nodiscard]] auto IsEmpty() const {
        return min.x > max.x || min.y > max.y || min.z > max.z;
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

    /**
     * @brief Translates the box by the specified offset.
     *
     * @param offset The offset to translate the box by.
     */
    auto Translate(const Vector3& offset) -> void;
};

}