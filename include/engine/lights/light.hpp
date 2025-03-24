// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/math/color.hpp"
#include "engine/nodes/node.hpp"

#include <memory>

namespace engine {

/**
 * @brief The type of light.
 */
enum class LightType {
    AmbientLight,
    DirectionalLight,
    PointLight,
    SpotLight
};

/**
 * @brief Abstract base class for light sources.
 */
class ENGINE_EXPORT Light : public Node {
public:
    /**
     * @brief Defines how the light intensity diminishes over distance.
     */
    struct Attenuation {
        /// @brief Minimum light intensity, unaffected by distance.
        float base {1.0f};
        /// @brief Controls a gradual, proportional fade as distance increases.
        float linear {0.0f};
        /// @brief Simulates real-world light falloff using an inverse-square law.
        float quadratic {0.0f};
    };

    /// @brief The color of the light.
    Color color {0xffffff};

    /// @brief The intensity of the light.
    float intensity {1.0f};

    /// @brief Indicates whether the light is in debug mode.
    bool debug_mode_enabled {false};

    /**
     * @brief Constructs a new Light instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     */
    Light(Color color, float intensity) : color(color), intensity(intensity) {}

    /**
     * @brief Retrieves the type of the light.
     *
     * @return LightType The type of the light.
     */
    [[nodiscard]] virtual auto Type() const -> LightType = 0;

    /**
     * @brief Enables or disables the debug mode for the light.
     *
     * @param is_debug_mode Indicates whether the debug mode should be enabled.
     */
    virtual auto SetDebugMode(bool is_debug_mode) -> void {
        debug_mode_enabled = is_debug_mode;
    }
};

}