/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/geometries/geometry.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Generates a cylinder geometry assignable to any mesh.
 *
 * `CylinderGeometry` creates a 3D cylinder composed of triangle primitives,
 * with configurable top and bottom radii, height, and segment subdivisions.
 * It can also be open-ended, excluding the caps.
 *
 * @code
 * auto geometry = gl3x::CylinderGeometry::Create({
 *     .radius_top = 0.8f,
 *     .radius_bottom = 1.0f,
 *     .height = 2.5f,
 *     .radial_segments = 32,
 *     .height_segments = 3,
 *     .open_ended = false
 * });
 *
 * auto mesh = gl3x::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class VGLX_EXPORT CylinderGeometry : public Geometry {
public:
    struct Parameters {
        float radius_top {1.0f}; ///< Top radius of the cylinder.
        float radius_bottom {1.0f}; ///< Bottom radius of the cylinder.
        float height {1.0f}; ///< Height of the cylinder.
        unsigned int radial_segments {32}; ///< Subdivisions along the radius.
        unsigned int height_segments {1}; ///< Subdivisions along the height.
        bool open_ended {false}; ///< Whether the cylinder is open ended.
    };

    /**
     * @brief Constructs a CylinderGeometry object.
     *
     * @param params CylinderGeometry::Parameters
     */
    explicit CylinderGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a CylinderGeometry object with default parameters.
     *
     * @return std::shared_ptr<CylinderGeometry>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<CylinderGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a CylinderGeometry object.
     *
     * @param params CylinderGeometry::Parameters
     * @return std::shared_ptr<CylinderGeometry>
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<CylinderGeometry>(params);
    }
};

}