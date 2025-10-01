/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/geometries/geometry.hpp"

namespace gleam {

/**
 * @brief Converts triangle-based geometry into wireframe-renderable geometry.
 *
 * `WireframeGeometry` takes an existing indexed geometry and generates a new
 * geometry that can be rendered using `GeometryPrimitiveType::Lines`. It
 * preserves the original vertex data and replaces the index buffer with one
 * that represents the edges of the original triangle mesh.
 *
 * This is commonly used for debugging purposes, such as visualizing mesh
 * topology, bounding volumes, or silhouette edges.
 *
 * @note The source geometry must be triangle-based and contain valid index data.
 *
 * @code
 * auto original = gleam::BoxGeometry::Create();
 * auto wireframe = std::make_shared<gleam::WireframeGeometry>(original.get());
 * mesh->geometry = wireframe;
 * @endcode
 *
 * @ingroup GeometryGroup
 */
class GLEAM_EXPORT WireframeGeometry : public Geometry {
public:
    /**
     * @brief Constructs a WireframeGeometry object from an existing geometry.
     *
     * @param geometry Pointer to the original triangle-based geometry.
     */
    explicit WireframeGeometry(const Geometry* geometry);

    /**
     * @brief Creates a shared pointer to a WireframeGeometry object.
     *
     * @param geometry Pointer to the original triangle-based geometry.
     * @return std::shared_ptr<WireframeGeometry>
     */
    [[nodiscard]] static auto Create(const Geometry* geometry) {
        return std::make_shared<WireframeGeometry>(geometry);
    }
};

}