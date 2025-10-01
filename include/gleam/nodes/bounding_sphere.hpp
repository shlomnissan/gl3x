/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/color.hpp"
#include "gleam/math/sphere.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Debug node that renders a bounding sphere.
 *
 * `BoundingSphere` is a visual helper used to display a wireframe sphere representing
 * the spatial bounds of an object or volume. It is primarily used for debugging,
 * spatial queries, or visibility testing.
 *
 * The sphere is defined in local space using a `Sphere` object and rendered as
 * a wireframe in the specified color.
 *
 * @code
 * auto geometry = gleam::BoxGeometry::Create();
 * auto bounds = gleam::BoundingSphere::Create(
 *   geometry->BoundingSphere(),
 *   0xFF0000
 * );
 * scene->Add(bounds);
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT BoundingSphere : public Node {
public:
    /**
     * @brief Constructs a BoundingSphere object.
     *
     * @param sphere Bounding sphere to visualize.
     * @param color Color used to render the bounding sphere.
     */
    BoundingSphere(const Sphere& sphere, const Color& color);

    /**
     * @brief Creates a shared pointer to a BoundingSphere object.
     *
     * @param sphere Bounding sphere to visualize.
     * @param color Color used to render the bounding sphere.
     * @return std::shared_ptr<BoundingSphere>
     */
    [[nodiscard]] static auto Create(const Sphere& sphere, const Color& color) {
        return std::make_shared<BoundingSphere>(sphere, color);
    }
};

}