/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"
#include "gleam/math/utilities.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Generates a sphere geometry assignable to any mesh.
 *
 * `SphereGeometry` creates a UV sphere composed of triangles, configurable
 * via radius, width segments (longitude), and height segments (latitude).
 * It’s useful for rendering planets, lighting probes, collision volumes,
 * or decorative primitives.
 *
 * @code
 * auto geometry = gleam::SphereGeometry::Create({
 *     .radius = 1.5f,
 *     .width_segments = 48,
 *     .height_segments = 24
 * });
 *
 * auto mesh = gleam::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT SphereGeometry : public Geometry {
public:
    /// @brief Parameters for constructing a SphereGeometry object.
    struct Parameters {
        float radius {1.0f}; ///< Radius of the sphere.
        unsigned width_segments {32}; ///< Subdivisions along the width.
        unsigned height_segments {16}; ///< Subdivisions along the height.
    };

    /**
     * @brief Constructs a SphereGeometry object.
     *
     * @param params SphereGeometry::Parameters
     */
    explicit SphereGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a SphereGeometry object with default parameters.
     *
     * @return std::shared_ptr<SphereGeometry>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<SphereGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a SphereGeometry object.
     *
     * @param params SphereGeometry::Parameters
     * @return std::shared_ptr<SphereGeometry>
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<SphereGeometry>(params);
    }
};

}