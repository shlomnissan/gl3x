// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/math/sphere.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

/**
 * @brief Represents a plane in 3D space.
 */
class ENGINE_EXPORT Plane {
public:
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
      : normal_(normal), distance_(distance) {}

    /**
     * @brief Returns the normal of the plane.
     *
     * @return The normal of the plane as a Vector3.
     */
    [[nodiscard]] auto Normal() const { return normal_; }

    /**
     * @brief Returns the signed distance of the plane from the origin.
     *
     * @return The signed distance of the plane.
     */
    [[nodiscard]] auto Distance() const { return distance_; }

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

private:
    /// @brief The normal of the plane.
    Vector3 normal_ {Vector3::Up()};

    /// @brief The signed distance of the plane from the origin.
    float distance_ {0.0f};
};

}