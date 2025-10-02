/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/geometries/cylinder_geometry.hpp"
#include "gl3x/geometries/geometry.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Generates a cone geometry assignable to any mesh.
 *
 * `ConeGeometry` creates a 3D cone shape with configurable radius, height,
 * and segment subdivisions. It is rendered using triangle primitives and can
 * optionally exclude the bottom cap (open-ended).
 *
 * @code
 * auto geometry = gl3x::ConeGeometry::Create({
 *   .radius = 0.5f,
 *   .height = 2.0f,
 *   .radial_segments = 32,
 *   .height_segments = 4,
 *   .open_ended = false
 * });
 *
 * auto mesh = gl3x::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class GL3X_EXPORT ConeGeometry : public CylinderGeometry {
public:
    /// @brief Parameters for constructing a ConeGeometry object.
    struct Parameters {
        float radius {1.0f}; ///< Radius of the cone.
        float height {1.0f}; ///< Height of the cone.
        unsigned radial_segments {16}; ///< Subdivisions along the radius.
        unsigned height_segments {1}; ///< Subdivisions along the height.
        bool open_ended {false}; ///< Whether the cone is open ended.
    };

    /**
     * @brief Constructs a ConeGeometry object.
     *
     * @param params ConeGeometry::Parameters
     */
    explicit ConeGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a ConeGeometry object with default parameters.
     *
     * @return std::shared_ptr<ConeGeometry>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<ConeGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a ConeGeometry object.
     *
     * @param params ConeGeometry::Parameters
     * @return std::shared_ptr<ConeGeometry>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<ConeGeometry>(params);
    }
};

}