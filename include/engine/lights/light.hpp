// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/color.hpp"
#include "engine/scene/node.hpp"

namespace engine {

/**
 * @brief Enum representing the type of light.
 */
enum class LightType {
    Ambient,        ///< Ambient light.
    Directional,    ///< Directional light.
    Spotlight       ///< Spotlight.
};

/**
 * @brief Class representing a light source in the scene.
 *
 * This abstract class provides a base for different types of lights,
 * including ambient, directional, and spotlight. It defines common properties
 * such as color and intensity, which can be used by derived light types.
 */
class ENGINE_EXPORT Light : public Node {
public:
    /// @brief The color of the light.
    Color color;
    /// @brief The intensity of the light.
    float intensity;

    /**
     * @brief Constructs a Light object with specified color and intensity.
     *
     * @param color The color of the light, default is white.
     * @param intensity The intensity of the light, default is 1.0f.
     */
    Light(Color color = {0xffffff}, float intensity = 1.0f)
        : color(color), intensity(intensity) {}

    /**
     * @brief Pure virtual function to get the type of the light.
     *
     * @return Light::Type The type of the light.
     */
    [[nodiscard]] virtual auto Type() const -> LightType = 0;

    /**
     * @brief Default destructor for the Light class.
     */
    ~Light() override = default;
};

}