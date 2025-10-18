/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/math/vector3.hpp"
#include "vglx/math/utilities.hpp"

namespace vglx {

/**
 * @brief Spherical coordinates (radius, phi, theta).
 *
 * Represents a point in 3D using spherical coordinates:
 * - `radius` is the distance from the origin.
 * - `phi` is the azimuth angle (yaw) in radians.
 * - `theta` is the polar angle (pitch) from the equator in radians.
 *
 * This is useful for orbital camera rigs, sampling directions on a sphere,
 * and converting to/from Cartesian coordinates.
 *
 * @ingroup MathGroup
 */
struct VGLX_EXPORT Spherical {
    float radius = 1.0f; ///< Radial distance from the origin.
    float phi = 0.0f; ///< Azimuth angle (yaw) in radians.
    float theta = 0.0f; ///< Polar angle (pitch) in radians.

    /**
     * @brief Default constructor.
     */
    constexpr Spherical() = default;

    /**
     * @brief Constructs a spherical coordinate from radius, phi, and theta.
     *
     * @param radius Radial distance from the origin.
     * @param phi Azimuth angle (yaw) in radians.
     * @param theta Polar angle (pitch) in radians.
     */
    constexpr Spherical(float radius, float phi, float theta)
        : radius(radius), phi(phi), theta(theta) {}

    /**
     * @brief Clamps @ref theta (polar) away from the poles.
     *
     * Keeps `theta` within (-π/2 + ε, π/2 − ε) to avoid degeneracy
     * where the azimuth angle becomes undefined and orientation calculations
     * (e.g. cross products for basis vectors) can break down.
     */
    constexpr auto MakeSafe() {
        const float limit = math::pi_over_2 - math::eps;
        theta = math::Clamp(theta, -limit, limit);
    }

    /**
     * @brief Converts spherical to Cartesian coordinates.
     *
     * Convention:
     * - `phi` (azimuth): 0 along +Z, increasing toward +X.
     * - `theta` (polar): 0 on the equator, +π/2 at +Y.
     *
     * @return vglx::Vector3 Cartesian vector (x, y, z).
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