/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/vector3.hpp"
#include "gleam/math/utilities.hpp"

#include <algorithm>

namespace gleam {

/**
 * @brief Spherical coordinates (radius, phi, theta).
 *
 * Represents a point in 3D using spherical coordinates:
 * - `radius` is the distance from the origin.
 * - `phi` is the azimuth (yaw) in radians.
 * - `theta` is the elevation (pitch) from the equator in radians.
 *
 * This is useful for orbital camera rigs, sampling directions on a sphere,
 * and converting to/from Cartesian coordinates.
 *
 * @ingroup MathGroup
 */
struct GLEAM_EXPORT Spherical {
    float radius = 1.0f; ///< Radial distance from the origin.
    float phi = 0.0f; ///< Azimuth (yaw) in radians.
    float theta = 0.0f; ///< Elevation (pitch) in radians.

    /**
     * @brief Default constructor.
     */
    constexpr Spherical() = default;

    /**
     * @brief Constructs a spherical coordinate from radius, phi, and theta.
     *
     * @param radius Radial distance from the origin.
     * @param phi Azimuth (yaw) in radians.
     * @param theta Elevation (pitch) in radians.
     */
    constexpr Spherical(float radius, float phi, float theta)
        : radius(radius), phi(phi), theta(theta) {}

    /**
     * @brief Clamps @ref theta (elevation) away from the poles.
     *
     * Keeps `theta` within (-π/2 + ε, π/2 − ε) to avoid degeneracy
     * where the azimuth becomes undefined and orientation calculations
     * (e.g. cross products for basis vectors) can break down.
     */
    constexpr auto MakeSafe() {
        const float lo = -math::pi_over_2 + math::eps;
        const float hi = math::pi_over_2 - math::eps;
        theta = std::clamp(theta, lo, hi);
    }

    /**
     * @brief Converts spherical to Cartesian coordinates.
     *
     * Convention:
     * - `phi` (azimuth): 0 along +Z, increasing toward +X.
     * - `theta` (elevation): 0 on the equator, +π/2 at +Y.
     *
     * @return gleam::Vector3 Cartesian vector (x, y, z).
     *
     * @see MakeSafe
     */
    [[nodiscard]] constexpr auto ToVector3() const {
        const auto c = math::Cos(theta);
        return Vector3 {
            radius * math::Sin(phi) * c,
            radius * math::Sin(theta),
            radius * math::Cos(phi) * c
        };
    }
};

}