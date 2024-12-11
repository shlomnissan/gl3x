// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/color.hpp"
#include "engine/nodes/mesh.hpp"
#include "engine/nodes/node.hpp"

#include <memory>

namespace engine {

/**
 * @brief A finite grid that is rendered in the scene.
 */
class ENGINE_EXPORT Grid : public Node {
public:
    /**
     * @brief Parameters used to create a grid.
     */
    struct Parameters {
        int dimensions; ///< The number of grid lines.
        float scale;    ///< The distance between each grid line.
        Color color;    ///< The color of the grid lines.
    };

    /**
     * @brief Constructs a Grid object with the given parameters.
     *
     * @param params The parameters used to create the grid.
     */
    explicit Grid(const Parameters& params);

    /**
     * @brief Creates a Grid object with the given parameters.
     *
     * @param params The parameters used to create the grid.
     * @return A shared pointer to the created Grid object.
     */
    static auto Create(const Parameters& params) {
        return std::make_shared<Grid>(params);
    }

private:
    /// @brief The mesh that represents the grid.
    std::shared_ptr<Mesh> mesh_;

    /**
     * @brief Creates the geometry for the grid.
     *
     * @param dimensions The number of grid lines.
     * @return A shared pointer to the created geometry.
     */
    auto CreateGeometry(const Parameters& params) const -> std::shared_ptr<Geometry>;
};

}