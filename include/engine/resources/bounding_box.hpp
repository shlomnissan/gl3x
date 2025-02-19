// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/core/geometry.hpp"
#include "engine/math/box3.hpp"
#include "engine/nodes/mesh.hpp"
#include "engine/nodes/node.hpp"

#include <memory>

namespace engine {

/**
 * @brief Generates line geometry from an axis-aligned bounding box.
 */
class ENGINE_EXPORT BoundingBox : public Node {
public:
    /**
     * @brief Constructs a BoundingBox object.
     *
     * @param box The box to draw.
     */
    explicit BoundingBox(const Box3& box);

    /**
     * @brief Creates a new instance of the BoundingBox class.
     *
     * @param box The box to draw.
     * @return A `std::shared_ptr<BoundingBox>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const Box3& box) {
        return std::make_shared<BoundingBox>(box);
    }

private:
    /// @brief The mesh that represents the bounding box.
    std::shared_ptr<Mesh> mesh_;

    /**
     * @brief Creates the geometry for the bounding box.
     *
     * @param box The box to draw.
     * @return A shared pointer to the created geometry.
     */
    auto CreateGeometry(const Box3& box) const -> std::shared_ptr<Geometry>;
};

}