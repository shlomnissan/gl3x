/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/geometries/geometry.hpp"
#include "vglx/math/utilities.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Generates a sphere geometry assignable to any mesh.
 *
 * `SphereGeometry` creates a UV sphere composed of triangles, configurable
 * via radius, width segments (longitude), and height segments (latitude).
 * It’s useful for rendering planets, lighting probes, collision volumes,
 * or decorative primitives.
 *
 * @code
 * auto geometry = gl3x::SphereGeometry::Create({
 *     .radius = 1.5f,
 *     .width_segments = 48,
 *     .height_segments = 24
 * });
 *
 * auto mesh = gl3x::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class VGLX_EXPORT SphereGeometry : public Geometry {
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