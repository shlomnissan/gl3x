// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/math/color.hpp"
#include "engine/math/plane.hpp"
#include "engine/nodes/node.hpp"

namespace engine {

/**
 * @brief Generates geometry to visualize an engine::Plane object.
 */
class ENGINE_EXPORT BoundingPlane : public Node {
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
     * @brief Creates the geometry for the bounding plane.
     *
     * @param plane The plane to draw.
     * @param size The size of the plane.
     * @return A shared pointer to the created geometry.
     */
    auto CreateGeometry(const Plane& plane, float size) const -> std::shared_ptr<Geometry>;
};

}