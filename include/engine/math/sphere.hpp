// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/math/vector3.hpp"

namespace engine {

/**
 * @brief Represents a sphere in 3D space.
 */
class ENGINE_EXPORT Sphere {
public:
    /**
     * @brief Constructs a sphere with the specified center and radius.
     *
     * @param center The center of the sphere.
     * @param radius The radius of the sphere.
     */
    Sphere(
        const Vector3 center = Vector3::Zero(),
        float radius = -1.0f
    ) : center_(center), radius_(radius) {}

    /**
     * @brief Retrieves the center of the sphere.
     *
     * @return The center of the sphere as a Vector3.
     */
    [[nodiscard]] auto Center() const -> Vector3 { return center_; }

    /**
     * @brief Retrieves the radius of the sphere.
     *
     * @return The radius of the sphere.
     */
    [[nodiscard]] auto Radius() const -> float { return radius_; }

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
        return radius_ < 0.0f;
    }

    /**
     * @brief Expands the sphere to include the specified point.
     *
     * @param p The point to include in the sphere.
     */
    auto ExpandWithPoint(const Vector3& p) -> void;

private:
    /// @brief The center of the sphere.
    Vector3 center_;

    /// @brief The radius of the sphere.
    float radius_;
};

}