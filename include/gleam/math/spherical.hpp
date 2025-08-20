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
 * - `phi` is the polar angle in radians (0 at the “north pole”, π at the “south pole”).
 * - `theta` is the azimuthal angle in radians around the up axis.
 *
 * This is useful for orbital camera rigs, sampling directions on a sphere,
 * and converting to/from Cartesian coordinates.
 *
 * @ingroup MathGroup
 */
struct GLEAM_EXPORT Spherical {
    /**
     * @brief Radial distance from the origin.
     *
     * Must be non‑negative for a valid position; a value of 0 collapses to the origin.
     */
    float radius = 1.0f;

    /**
     * @brief Polar angle in radians.
     *
     * Ranges from 0 (north pole) to π (south pole). Values very close to the poles
     * can lead to numerical instability in some conversions; see MakeSafe().
     */
    float phi = 0.0f;

    /**
     * @brief Azimuthal angle in radians around the up axis.
     *
     * Typically wrapped to the range [-π, π) or [0, 2π) by user code as needed.
     */
    float theta = 0.0f;

    /**
     * @brief Constructs a spherical coordinate from radius, phi, and theta.
     *
     * @param radius Radial distance from the origin.
     * @param phi Polar angle in radians.
     * @param theta Azimuthal angle in radians around the up axis.
     */
    constexpr Spherical(float radius, float phi, float theta)
        : radius(radius), phi(phi), theta(theta) {}

    /**
     * @brief Clamps @ref phi away from the singularities at the poles.
     *
     * Ensures `phi` is within (ε, π − ε), where ε is a small constant to avoid
     * degenerate cases during conversions and orientation calculations.
     */
    constexpr auto MakeSafe() {
        phi = std::clamp(phi, math::eps, math::pi - math::eps);
    }
};

}