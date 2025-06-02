/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/sphere.hpp"
#include "gleam/math/vector3.hpp"

namespace gleam {

/**
 * @brief Represents a plane in 3D space.
 */
struct GLEAM_EXPORT Plane {
    /// @brief The normal of the plane.
    Vector3 normal {Vector3::Up()};

    /// @brief The signed distance of the plane from the origin.
    float distance {0.0f};

    /**
     * @brief Construct a new Plane object.
     */
    Plane() = default;

    /**
     * @brief Constructs a plane with the specified normal and signde distance.
     *
     * @param normal The normal of the plane.
     * @param distance The signed distance from the origin.
     */
    Plane(const Vector3& normal, float distance)
      : normal(normal), distance(distance) {}

    /**
     * @brief Returns the distance from the plane to a point.
     *
     * @param point The point to calculate the distance to.
     * @return The distance from the plane to a point.
     */
    [[nodiscard]] auto DistanceToPoint(const Vector3& point) const -> float;

    /**
     * @brief Returns the distance from the plane to a sphere.
     *
     * @param sphere The sphere to calculate the distance to.
     * @return The distance from the plane to the sphere.
     */
    [[nodiscard]] auto DistanceToSphere(const Sphere& sphere) const -> float;

    /**
     * @brief Normalizes the plane normal and adjusts the distance accordingly.
     */
    auto Normalize() -> void;
};

}