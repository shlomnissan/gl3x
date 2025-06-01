// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"
#include "gleam/math/color.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

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
 * @brief Base class for light objects. It provides a common interface for
 * all light types. Not intended to be instantiated directly.
 *
 * @ingroup LightsGroup
 */
class GLEAM_EXPORT Light : public Node {
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

    /// @brief Indicates whether the light is in debug mode.
    bool debug_mode_enabled {false};

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
    [[nodiscard]] virtual auto Type() const -> LightType = 0;

    /**
     * @brief Sets debug mode.
     *
     * @param is_debug_mode True to enable debug mode, false to disable.
     */
    virtual auto SetDebugMode(bool is_debug_mode) -> void {
        debug_mode_enabled = is_debug_mode;
    }
};

}