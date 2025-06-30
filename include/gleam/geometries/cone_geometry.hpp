/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/cylinder_geometry.hpp"
#include "gleam/geometries/geometry.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Generates a cone geometry assignable to any mesh.
 *
 * `ConeGeometry` creates a 3D cone shape with configurable radius, height,
 * and segment subdivisions. It is rendered using triangle primitives and can
 * optionally exclude the bottom cap (open-ended).
 *
 * @code
 * auto geometry = gleam::ConeGeometry::Create({
 *   .radius = 0.5f,
 *   .height = 2.0f,
 *   .radial_segments = 32,
 *   .height_segments = 4,
 *   .open_ended = false
 * });
 *
 * auto mesh = gleam::Mesh::Create(geometry, FlatMaterial::Create(0x049EF4));
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT ConeGeometry : public CylinderGeometry {
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