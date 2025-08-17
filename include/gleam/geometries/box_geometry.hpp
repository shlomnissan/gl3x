/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"
#include "gleam/math/vector3.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Generates a box geometry assignable to any mesh.
 *
 * `BoxGeometry` creates a 3D box or rectangular box composed of triangles,
 * based on configurable width, height, and depth. Optional segment parameters
 * allow for subdividing each face, enabling smoother lighting or custom
 * deformation effects.
 *
 * @code
 * auto geometry = gleam::BoxGeometry::Create({
 *   .width = 2.0f,
 *   .height = 1.0f,
 *   .depth = 3.0f,
 *   .width_segments = 2,
 *   .height_segments = 2,
 *   .depth_segments = 2
 * });
 *
 * auto mesh = gleam::Mesh::Create(geometry, UnlitMaterial::Create(0x049EF4));
 * my_scene->Add(mesh);
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT BoxGeometry : public Geometry {
public:
    /// @brief Parameters for constructing a BoxGeometry object.
    struct Parameters {
        float width {1.0f}; ///< Width of the box.
        float height {1.0f}; ///< Height of the box.
        float depth {1.0f}; ///< Depth of the box.
        unsigned width_segments {1}; ///< Subdivisions along the X-axis.
        unsigned height_segments {1}; ///< Subdivisions along the Y-axis.
        unsigned depth_segments {1}; ///< Subdivisions along the Z-axis.
    };

    /**
     * @brief Constructs a BoxGeometry object.
     *
     * @param params BoxGeometry::Parameters
     */
    explicit BoxGeometry(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a BoxGeometry object with default parameters.
     *
     * @return std::shared_ptr<BoxGeometry>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<BoxGeometry>(Parameters {});
    }

    /**
     * @brief Creates a shared pointer to a BoxGeometry object.
     *
     * @param params BoxGeometry::Parameters
     * @return std::shared_ptr<BoxGeometry>
     */
    [[nodiscard]] static auto Create(const Parameters& params){
        return std::make_shared<BoxGeometry>(params);
    }

private:
    /// @brief Internal counter used during generation.
    unsigned int vertex_counter_ {0};
};

}