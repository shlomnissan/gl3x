/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/color.hpp"
#include "gl3x/math/plane.hpp"
#include "gl3x/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Debug node that renders a bounding plane.
 *
 * `BoundingPlane` is a visual helper used to display an infinite mathematical plane
 * as a finite square region in the scene. This is particularly useful for visualizing
 * clipping planes, frustum culling boundaries, or geometry intersections during debugging.
 *
 * The plane is rendered as a flat square centered around the origin of the plane,
 * oriented using the plane’s normal vector, and scaled based on the specified size.
 *
 * @code
 * auto plane = gleam::Plane {Vector3::Forward(), 0.0f};
 * auto bounds = gleam::BoundingPlane::Create(plane, 2, 0xFF0000);
 * scene->Add(bounds);
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GL3X_EXPORT BoundingPlane : public Node {
public:
    /**
     * @brief Constructs a BoundingPlane object.
     *
     * @param plane Plane definition in 3D space.
     * @param size Length of the plane's rendered square region.
     * @param color Color used to render the plane.
     */
    BoundingPlane(const Plane& plane, float size, const Color& color);

    /**
     * @brief Creates a shared pointer to a BoundingPlane object.
     *
     * @param plane Plane definition in 3D space.
     * @param size Length of the plane's rendered square region.
     * @param color Color used to render the plane.
     * @return std::shared_ptr<BoundingPlane>
     */
    [[nodiscard]] static auto Create(const Plane& plane, float size, const Color& color) {
        return std::make_shared<BoundingPlane>(plane, size, color);
    }
};

}