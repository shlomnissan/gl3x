// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

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
     * @brief Retrieves the normal of the plane.
     *
     * @return The normal of the plane as a Vector3.
     */
    [[nodiscard]] auto Normal() const { return normal_; }

    /**
     * @brief Retrieves the signed distance of the plane from the origin.
     *
     * @return The signed distance of the plane.
     */
    [[nodiscard]] auto Distance() const { return distance_; }

private:
    /// @brief The normal of the plane.
    Vector3 normal_ {Vector3::Up()};

    /// @brief The signed distance of the plane from the origin.
    float distance_ {0.0f};
};

}