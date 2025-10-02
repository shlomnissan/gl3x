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
 * @brief Represents a light that emits in a specific direction with a
 * cone-shaped area of influence.
 *
 * The light intensity diminishes both with distance and with the angle from
 * the central axis of the cone. This type of light is commonly used to
 * simulate focused sources such as flashlights or stage spotlights, where
 * illumination is limited to a defined region and falls off outside of it.
 *
 * @code
 * auto spot_light = gleam::SpotLight::Create({
 *   .color = 0xFFFFFF,
 *   .intensity = 1.0f,
 *   .angle = gleam::math::DegToRad(10.0f),
 *   .penumbra = 0.3f,
 *   .target = nullptr,
 *   .attenuation = {
 *     .base = 1.0f,
 *     .linear = 0.0f,
 *     .quadratic = 0.0f
 *   }
 * });
 * @endcode
 *
 * When the target parameter is set to `nullptr` the light points to (0, 0, 0).
 *
 * @ingroup LightsGroup
 */
class GL3X_EXPORT SpotLight : public Light {
public:
    /// @brief Parameters for constructing a SpotLight object.
    struct Parameters {
        Color color; ///< Light color.
        float intensity; ///< Light intensity.
        float angle; ///< Cone angle (in radians) for spotlight cutoff.
        float penumbra; ///< Softness of the spotlight edge.
        std::shared_ptr<Node> target; ///< Light target position.
        Attenuation attenuation; ///< Light attenuation properties.
    };

    /// @brief Angle, in radians, of the spotlight's cone.
    float angle;

    /// @brief Penumbra value controlling the softness of the spotlight's edge.
    float penumbra;

    /// @brief Node that the light is directed towards.
    std::shared_ptr<Node> target {nullptr};

    /// @brief Light attenuation properties.
    Attenuation attenuation;

    /**
     * @brief Constructs a SpotLight object.
     *
     * @param params SpotLight::Parameters
     */
    explicit SpotLight(const Parameters& params);

    /**
     * @brief Creates a shared pointer to a SpotLight object.
     *
     * @param params SpotLight::Parameters
     * @return std::shared_ptr<SpotLight>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<SpotLight>(params);
    }

    /**
     * @brief Returns light type.
     *
     * @return LightType::SpotLight
     */
    [[nodiscard]] auto GetType() const -> LightType override {
        return LightType::SpotLight;
    }

    /**
     * @brief Returns the direction vector of the light.
     *
     * Calculates and returns the normalized direction in which the spotlight
     * is pointing. The direction is determined based on the light's position
     * and its target node.
     *
     * @return Vector3
     */
    [[nodiscard]] auto Direction() -> Vector3;

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
    ~SpotLight() override;

private:
    /// @cond INTERNAL
    struct Impl;
    std::unique_ptr<Impl> impl_;
    /// @endcond
};

}