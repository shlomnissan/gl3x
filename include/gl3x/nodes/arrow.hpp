/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/color.hpp"
#include "gl3x/math/vector3.hpp"
#include "gl3x/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Visual debug primitive representing a 3D arrow.
 *
 * `Arrow` is a scene node that renders a directional arrow from a given origin,
 * primarily used for debugging, orientation helpers, or coordinate indicators.
 * It is constructed from a shaft and cone head, scaled based on the provided length.
 *
 * The arrow can be positioned using `SetOrigin()` and oriented using `SetDirection()`.
 *
 * @code
 * auto arrow = gleam::Arrow::Create({
 *   .direction = {1.0f, 0.0f, 0.0f},
 *   .origin = Vector3::Zero(),
 *   .color = 0xFF0000,
 *   .length = 1.0f
 * });
 * scene->Add(arrow);
 * @endcode
 *
 * @ingroup NodesGroup
 */
class GL3X_EXPORT Arrow : public Node {
public:
    /// @brief Parameters for constructing an Arrow object.
    struct Parameters {
        Vector3 direction; ///< Direction of the arrow.
        Vector3 origin; ///< Origin of the arrow.
        Color color; ///< Color of the arrow.
        float length; ///< Length of the arrow.
    };

    /**
     * @brief Constructs an Arrow object.
     *
     * @param params Arrow::Parameters
     */
    explicit Arrow(const Parameters& params);

    /**
     * @brief Creates a shared pointer to an Arrow object.
     *
     * @param params Arrow::Parameters
     * @return std::shared_ptr<Arrow>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<Arrow>(params);
    }

    /**
     * @brief Sets the direction of the arrow.
     *
     * @param direction Direction of the arrow.
     */
    auto SetDirection(const Vector3& direction) -> void;

    /**
     * @brief Sets the origin of the arrow.
     *
     * @param origin Origin of the arrow.
     */
    auto SetOrigin(const Vector3& origin) -> void;
};

}