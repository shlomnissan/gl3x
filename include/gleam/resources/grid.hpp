/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/math/color.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief An object that defines a finite grid.
 */
class GLEAM_EXPORT Grid : public Node {
public:
    /**
     * @brief The parameters for the grid.
     */
    struct Parameters {
        float size;         ///< The size of the grid.
        unsigned divisions; ///< The number of divisions per side.
        Color color;        ///< The color of the grid.
    };

    /**
     * @brief Creates a new GridHelper of size 'size' and divided into
     * 'divisions' segments per side. Colors are optional.
     *
     * @param params The parameters for the grid.
     */
    explicit Grid(const Parameters& params);

    /**
     * @brief Creates a new instance of the Grid class.
     *
     * @param params The parameters for the grid.
     * @return A shared pointer to the instance of the grid.
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<Grid>(params);
    }
};

}