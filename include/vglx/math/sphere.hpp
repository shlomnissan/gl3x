/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/math/matrix4.hpp"
#include "vglx/math/utilities.hpp"
#include "vglx/math/vector3.hpp"

#include <algorithm>

namespace gl3x {

/**
 * @brief A bounding sphere defined by a center point and radius.
 *
 * Useful for fast intersection tests, frustum culling, and spatial bounds.
 *
 * @ingroup MathGroup
 */
struct VGLX_EXPORT Sphere {
    /// @brief Center of the sphere in 3D space.
    Vector3 center {Vector3::Zero()};

    /// @brief Radius of the sphere. A negative value indicates an empty sphere.
    float radius {-1.0f};

    /**
     * @brief Constructs a Sphere with a negative (empty) radius.
     */
    constexpr Sphere() = default;

    /**
     * @brief Constructs a Sphere from a center and a radius.
     *
     * @param center Center position.
     * @param radius Radius.
     */
    constexpr Sphere(const Vector3 center, float radius) :
        center(center),
        radius(radius) {}

    /**
     * @brief Returns the current radius of the sphere.
     *
     * @return Radius of the sphere.
     */
    [[nodiscard]] constexpr auto Radius() const { return radius; }

    /**
     * @brief Resets the sphere to an empty state.
     *
     * Sets the center to (0, 0, 0) and the radius to -1.
     */
    constexpr auto Reset() {
        center = Vector3::Zero();
        radius = -1.0f;
    }

    /**
     * @brief Checks if the sphere is empty.
     *
     * An empty sphere is defined by a negative radius.
     *
     * @return True if the sphere is empty, false otherwise.
     */
    [[nodiscard]] constexpr auto IsEmpty() const {
        return radius < 0.0f;
    }

    /**
     * @brief Expands the sphere to include a given point.
     *
     * If the sphere is empty, it is initialized with the point.
     * Otherwise, the sphere expands just enough to include the point.
     *
     * @param p Point to include in the sphere.
     */
    constexpr auto ExpandWithPoint(const Vector3& p) {
        // Handle the case where the sphere is empty (invalid).
        // In this case, the sphere is centered at the point and has a radius of 0.
        if (IsEmpty()) {
            center = p;
            radius = 0.0f;
            return;
        }

        const auto delta = p - center;
        const auto length_sqr = delta.LengthSquared();
        if (length_sqr > radius * radius) {
            const auto length = math::Sqrt(length_sqr);
            // Move the center halfway towards the new pointm and expand the radius
            // by half the distance to the new point.
            const auto half_way = (length - radius) * 0.5f;
            center += delta * (half_way / length);
            radius += half_way;
        }
    }

    /**
     * @brief Transforms the sphere by the given matrix.
     *
     * The center is transformed directly, and the radius is scaled
     * by the maximum scale component of the matrix.
     *
     * @param transform 4x4 matrix to apply to the sphere.
     */
    constexpr auto ApplyTransform(const Matrix4& transform) {
        center = transform * center;
        auto& t0 = transform[0];
        auto& t1 = transform[1];
        auto& t2 = transform[2];

        radius *= math::Sqrt(std::max({
            Vector3 {t0.x, t0.y, t0.z}.LengthSquared(),
            Vector3 {t1.x, t1.y, t1.z}.LengthSquared(),
            Vector3 {t2.x, t2.y, t2.z}.LengthSquared(),
        }));
    }

    /**
     * @brief Translates the sphere by a constant vector.
     *
     * @param translation Vector to translate by.
     */
    constexpr auto Translate(const Vector3& translation) {
        center += translation;
    }

    /**
     * @brief Expands this sphere to fully contain another sphere.
     *
     * @param other The sphere to merge into this one.
     *
     * @see ExpandWithPoint
     */
    constexpr auto Union(const Sphere& other) {
        if (other.IsEmpty()) return;

        if (IsEmpty()) {
            center = other.center;
            radius = other.radius;
            return;
        }

        if (center == other.center) {
            radius = std::max(radius, other.radius);
            return;
        }

        auto radius_dir = Normalize(other.center - center) * other.radius;
        ExpandWithPoint(other.center + radius_dir);
        ExpandWithPoint(other.center - radius_dir);
    }
};

}