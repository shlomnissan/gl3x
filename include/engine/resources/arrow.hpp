// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/math/color.hpp"
#include "engine/math/vector3.hpp"
#include "engine/nodes/node.hpp"

namespace engine {

/**
 * @brief Generates geometry to visualize an arrow in 3D space.
 */
class ENGINE_EXPORT Arrow : public Node {
public:
    /**
     * @brief Constructs an Arrow object with a direction, origin and length.
     *
     * @param direction The direction of the arrow (normalized).
     * @param origin The origin of the arrow.
     * @param color The color of the arrow.
     * @param length The length of the arrow.
     */
    Arrow(const Vector3& direction, const Vector3& origin, const Color& color, float length);

    /**
     * @brief Creates a new instance of the Arrow class.
     *
     * @param direction The direction of the arrow (normalized).
     * @param origin The origin of the arrow.
     * @param color The color of the arrow.
     * @param length The length of the arrow.
     * @return A `std::shared_ptr<Arrow>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create(
        const Vector3& direction,
        const Vector3& origin,
        const Color& color,
        float length
    ) -> std::shared_ptr<Arrow> {
        return std::make_shared<Arrow>(direction, origin, color, length);
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