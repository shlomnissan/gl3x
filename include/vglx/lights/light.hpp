/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/math/color.hpp"
#include "vglx/nodes/node.hpp"

#include <memory>

namespace vglx {

/**
 * @brief Represents available light types.
 * @ingroup LightsGroup
 */
enum class LightType {
    AmbientLight,
    DirectionalLight,
    PointLight,
    SpotLight
};

/**
 * @brief Abstract base class for light types.
 *
 * Not intended for direct use.
 *
 * @ingroup LightsGroup
 */
class VGLX_EXPORT Light : public Node {
public:
    /**
     * @brief Defines how light intensity diminishes over distance.
     */
    struct Attenuation {
        /// @brief Minimum light intensity, unaffected by distance.
        float base {1.0f};
        /// @brief Gradual, proportional fade as distance increases.
        float linear {0.0f};
        /// @brief Real-world light falloff using an inverse-square law.
        float quadratic {0.0f};
    };

    /// @brief Light color, represented as RGB values.
    Color color {0xffffff};

    /// @brief Light intensity.
    float intensity {1.0f};

    /**
     * @brief Constructs a Light object.
     *
     * @param color Light color.
     * @param intensity Light intensity.
     */
    Light(Color color, float intensity) : color(color), intensity(intensity) {}

    /**
     * @brief Returns light type.
     *
     * @return LightType
     */
    [[nodiscard]] virtual auto GetType() const -> LightType = 0;

    /**
     * @brief Returns node type.
     *
     * @return Node::Type::Light
     */
    [[nodiscard]] auto GetNodeType() const -> Node::Type override {
        return Node::Type::Light;
    }

    /**
     * @brief Sets debug mode.
     *
     * @param is_debug_mode True to enable debug mode, false to disable.
     */
    virtual auto SetDebugMode(bool is_debug_mode) -> void {
        debug_mode_enabled_ = is_debug_mode;
    }

    /**
     * @brief Virtual destructor.
     */
    ~Light() = default;

protected:
    bool debug_mode_enabled_ {false};
};

}