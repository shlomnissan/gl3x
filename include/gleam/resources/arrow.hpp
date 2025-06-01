// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"
#include "gleam/math/color.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Generates geometry to visualize an arrow in 3D space.
 */
class GLEAM_EXPORT Arrow : public Node {
public:
    struct Parameters {
        Vector3 direction;  ///< The direction of the arrow (normalized).
        Vector3 origin;     ///< The origin of the arrow.
        Color color;        ///< The color of the arrow.
        float length;       ///< The length of the arrow.
    };

    /**
     * @brief Constructs an Arrow object with a direction, origin and length.
     *
     * @param params Parameters for the arrow, including direction, origin, color, and length.
     */
    explicit Arrow(const Parameters& params);

    /**
     * @brief Creates a new instance of the Arrow class.
     *
     * @param params Parameters for the arrow, including direction, origin, color, and length.
     * @return std::shared_ptr<Arrow> pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(const Parameters& params) -> std::shared_ptr<Arrow> {
        return std::make_shared<Arrow>(params);
    }

    /**
     * @brief Sets the direction of the arrow.
     *
     * @param direction The direction of the arrow (normalized).
     */
    auto SetDirection(const Vector3& direction) -> void;

    /**
     * @brief Sets the origin of the arrow.
     *
     * @param origin The origin of the arrow.
     */
    auto SetOrigin(const Vector3& origin) -> void;
};

}