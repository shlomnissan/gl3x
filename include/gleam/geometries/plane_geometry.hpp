/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Generates a flat 2D plane geometry assignable to any mesh.
 *
 * `PlaneGeometry` creates a rectangular surface in the X-Y plane, suitable
 * for ground planes, walls, billboards, or UI backgrounds. It supports width
 * and height segmentation for effects like displacement or tesselation.
 *
 * @code
 * auto geometry = gleam::PlaneGeometry::Create({
 *     .width = 5.0f,
 *     .height = 3.0f,
 *     .width_segments = 2,
 *     .height_segments = 2
 * });
 *
 * auto mesh = gleam::Mesh::Create(geometry, FlatMaterial::Create(0x049EF4));
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT PlaneGeometry : public Geometry {
public:
    /// @brief Parameters for constructing a PlaneGeometry object.
    struct Parameters {
        float width {1.0f}; ///< Width of the plane.
        float height {1.0f}; ///< Height of the plane.
        unsigned width_segments {1}; ///< Subdivisions along the width.
        unsigned height_segments {1}; ///< Subdivisions along the height.
    };

    /**
     * @brief Constructs a PlaneGeometry object.
     *
     * @param params PlaneGeometry::Parameters
     */
    explicit PlaneGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a PlaneGeometry object with default parameters.
     *
     * @return std::shared_ptr<PlaneGeometry>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<PlaneGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a PlaneGeometry object.
     *
     * @param params PlaneGeometry::Parameters
     * @return std::shared_ptr<PlaneGeometry>
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<PlaneGeometry>(params);
    }
};

}