/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/core/geometry.hpp"
#include "gleam/math/color.hpp"
#include "gleam/math/plane.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Generates geometry to visualize an gleam::Plane object.
 */
class GLEAM_EXPORT BoundingPlane : public Node {
public:
    /**
     * @brief Constructs a BoundingPlane object with a plane, size and color.
     *
     * @param plane The plane to draw.
     * @param size The size of the plane.
     * @param color The color of the bounding plane.
     */
    BoundingPlane(const Plane& plane, float size, const Color& color);

    /**
     * @brief Creates a new instance of the BoundingPlane class.
     *
     * @param plane The plane to draw.
     * @param size The size of the plane.
     * @param color The color of the bounding plane.
     * @return A `std::shared_ptr<BoundingPlane>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const Plane& plane, float size, const Color& color) {
        return std::make_shared<BoundingPlane>(plane, size, color);
    }

private:
    /**
     * @brief Creates the wireframe geometry for the bounding plane.
     *
     * @param color The color of the bounding plane.
     */
    auto CreateWireframeMesh(const Color& color) -> void;

    /**
     * @brief Creates a solid mesh for the bounding plane.
     *
     * @param color The color of the bounding plane.
     */
    auto CreateSolidMesh(const Color& color) -> void;
};

}