/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/box3.hpp"
#include "gl3x/math/color.hpp"
#include "gl3x/nodes/node.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Debug node that renders an axis-aligned bounding box.
 *
 * `BoundingBox` is a visual helper used to display a wireframe box representing
 * the spatial bounds of an object or region. It is commonly used for debugging,
 * collision visualization, or spatial partitioning diagnostics.
 *
 * The box is defined in local space using a `Box3` volume and rendered as
 * lines in the specified color.
 *
 * @code
 * auto geometry = gl3x::SphereGeometry::Create();
 * auto bounds = gl3x::BoundingBox::Create(
 *   geometry->BoundingBox(),
 *   0xFFFFFF
 * );
 * scene->Add(bounds);
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GL3X_EXPORT BoundingBox : public Node {
public:
    /**
     * @brief Constructs a BoundingBox object.
     *
     * @param box Axis-aligned bounding box to visualize.
     * @param color Color used to render the bounding box lines.
     */
    BoundingBox(const Box3& box, const Color& color);

    /**
     * @brief Creates a shared pointer to a BoundingBox object.
     *
     * @param box Axis-aligned bounding box to visualize.
     * @param color Color used to render the bounding box lines.
     * @return std::shared_ptr<BoundingBox>
     */
    [[nodiscard]] static auto Create(const Box3& box, const Color& color) {
        return std::make_shared<BoundingBox>(box, color);
    }
};

}