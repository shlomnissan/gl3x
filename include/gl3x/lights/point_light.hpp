/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/lights/light.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Represents a light that gets emitted from a single point in all directions.
 *
 * A common use case for this is to replicate the light emitted from a bare lightbulb.
 *
 * @code
 * auto point_light = gleam::PointLight::Create({
 *   .color = 0xFFFFFF,
 *   .intensity = 1.0f,
 *   .attenuation = {
 *     .base = 1.0f,
 *     .linear = 0.0f,
 *     .quadratic = 0.0f
 *   }
 * });
 * @endcode
 *
 * @ingroup LightsGroup
 */
class GL3X_EXPORT PointLight : public Light {
public:
    /// @brief Parameters for constructing a PointLight object.
    struct Parameters {
        Color color; ///< Light color.
        float intensity; ///< Light intensity.
        Attenuation attenuation; ///< Light attenuation properties.
    };

    /// @brief Light attenuation properties.
    Attenuation attenuation;

    /**
     * @brief Constructs a PointLight object.
     *
     * @param params PointLight::Parameters
     */
    PointLight(const Parameters& params);

    /**
     * @brief Creates a shared pointer to an PointLight object.
     *
     * @param params PointLight::Parameters
     * @return std::shared_ptr<PointLight>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<PointLight>(params);
    }

    /**
     * @brief Returns light type.
     *
     * @return LightType::PointLight
     */
    [[nodiscard]] auto GetType() const -> LightType override {
        return LightType::PointLight;
    }

    /**
     * @brief Sets debug mode.
     *
     * @param is_debug_mode True to enable debug mode, false to disable.
     */
    auto SetDebugMode(bool is_debug_mode) -> void override;

    /**
     * @brief Updates the light each frame.
     *
     * @param delta Time in seconds since the last update.
     */
    auto OnUpdate(float delta) -> void override;

    /**
     * @brief Destructor.
     */
    ~PointLight() override;

private:
    /// @cond INTERNAL
    struct Impl;
    std::unique_ptr<Impl> impl_;
    /// @endcond
};

}