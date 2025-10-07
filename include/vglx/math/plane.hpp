/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/math/sphere.hpp"
#include "vglx/math/utilities.hpp"
#include "vglx/math/vector3.hpp"

namespace vglx {

/**
 * @brief A plane defined by a normal vector and a distance from the origin.
 *
 * The plane equation is defined as: dot(normal, point) + distance = 0.
 * Used in collision tests, frustum culling, and geometry classification.
 *
 * @ingroup MathGroup
 */
struct VGLX_EXPORT Plane {
    /// @brief The normal vector of the plane, pointing outward.
    Vector3 normal {Vector3::Up()};

    /// @brief The signed distance from the origin to the plane along the normal.
    float distance {0.0f};

    /**
     * @brief Constructs a Plane with an upward normal and zero distance.
     */
    constexpr Plane() = default;

    /**
     * @brief Constructs a Plane from a normal vector and distance.
     *
     * @param normal Normal vector of the plane.
     * @param distance Signed distance from the origin.
     */
    constexpr Plane(const Vector3& normal, float distance) :
        normal(normal),
        distance(distance) {}

    /**
     * @brief Returns the signed distance from a point to the plane.
     *
     * Positive values mean the point is in front of the plane (in the direction of the normal),
     * negative values mean it's behind.
     *
     * @param point The point to measure.
     * @return Signed distance from the point to the plane.
     */
    [[nodiscard]] constexpr auto DistanceToPoint(const Vector3& point) const {
        return Dot(normal, point) + distance;
    }

    /**
     * @brief Returns the signed distance from a sphere to the plane.
     *
     * A negative result means the sphere intersects or is behind the plane.
     *
     * @param sphere The sphere to measure.
     * @return Signed distance from the sphere to the plane.
     */
    [[nodiscard]] constexpr auto DistanceToSphere(const Sphere& sphere) const {
        return DistanceToPoint(sphere.center) - sphere.radius;
    }

     /**
     * @brief Normalizes the plane equation.
     *
     * Ensures the normal is unit length and adjusts the distance accordingly.
     */
    constexpr auto Normalize() {
        const auto inverse_length = math::InverseSqrt(Dot(normal, normal));
        normal *= inverse_length;
        distance *= inverse_length;
    }
};

}