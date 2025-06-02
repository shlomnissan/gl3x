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

namespace gleam {

/**
 * @brief Represents a sphere in 3D space.
 */
struct GLEAM_EXPORT Sphere {
    /// @brief The center of the sphere.
    Vector3 center {Vector3::Zero()};

    /// @brief The radius of the sphere.
    float radius {-1.0f};

    /**
     * @brief Constructs a new Sphere object.
     */
    Sphere() = default;

    /**
     * @brief Constructs a sphere with the specified center and radius.
     *
     * @param center The center of the sphere.
     * @param radius The radius of the sphere.
     */
    Sphere(const Vector3 center, float radius)
      : center(center), radius(radius) {}

    /**
     * @brief Retrieves the radius of the sphere.
     *
     * @return The radius of the sphere.
     */
    [[nodiscard]] auto Radius() const -> float { return radius; }

    /**
     * @brief Resets the sphere to its empty state.
     */
    auto Reset() -> void;

    /**
     * @brief Checks if the sphere is empty.
     *
     * @return True if the sphere is empty, false otherwise.
     */
    [[nodiscard]] auto IsEmpty() const {
        return radius < 0.0f;
    }

    /**
     * @brief Expands the sphere to include the specified point.
     *
     * @param p The point to include in the sphere.
     */
    auto ExpandWithPoint(const Vector3& p) -> void;

    /**
     * @brief Transforms the sphere by the specified matrix.
     *
     * @param transform The matrix to apply to the sphere.
     */
    auto ApplyTransform(const Matrix4& transform) -> void;

    /**
     * @brief Translates the sphere by the specified offset.
     *
     * @param offset The offset to translate the sphere by.
     */
    auto Translate(const Vector3& offset) -> void;
};

}