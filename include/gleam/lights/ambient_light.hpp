// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam/lights/light.hpp"

#include <memory>

namespace engine {

/**
 * @brief  a light that gets emitted in all directions equally.
 * This light cannot be used to cast shadows as it does not have a direction.
 *
 * @code
 * Add(AmbientLight::Create({
 *   .color = 0xFFFFFF,
 *   .intensity = 0.3f
 * }));
 * @endcode
 *
 * @ingroup LightsGroup
 */
class AmbientLight : public Light {
public:
    /// @brief Parameters for constructing an AmbientLight object.
    struct Parameters {
        Color color; ///< Light color.
        float intensity; ///< Light intensity.
    };

    /**
     * @brief Constructs an AmbientLight object.
     *
     * @param params AmbientLight::Parameters
     */
    explicit AmbientLight(const Parameters& params) : Light(params.color, params.intensity) {
        SetName("ambient light");
    }

    /**
     * @brief Creates a shared pointer to an AmbientLight object.
     *
     * @param params AmbientLight::Parameters
     * @return std::shared_ptr<AmbientLight>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<AmbientLight>(params);
    }

    /**
     * @brief Returns light type.
     *
     * @return LightType::Ambient
     */
    [[nodiscard]] auto Type() const -> LightType override {
        return LightType::AmbientLight;
    }
};

}