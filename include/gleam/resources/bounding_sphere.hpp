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
#include "gleam/math/sphere.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Generates geometry to visualize an gleam::Sphere object.
 *
 */
class GLEAM_EXPORT BoundingSphere : public Node {
public:
    /**
     * @brief Constructs a BoundingSphere object with a sphere and color.
     *
     * @param sphere The sphere to draw.
     * @param color The color of the bounding sphere.
     */
    BoundingSphere(const Sphere& sphere, const Color& color);

    /**
     * @brief Creates a new instance of the BoundingSphere class.
     *
     * @param sphere The sphere to draw.
     * @param color The color of the bounding sphere.
     * @return A `std::shared_ptr<BoundingSphere>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const Sphere& sphere, const Color& color) {
        return std::make_shared<BoundingSphere>(sphere, color);
    }

private:
    /**
     * @brief Creates the geometry for the bounding sphere.
     *
     * @param sphere The sphere to draw.
     * @return A shared pointer to the created geometry.
     */
    auto CreateGeometry(const Sphere& sphere) const -> std::shared_ptr<Geometry>;
};

}