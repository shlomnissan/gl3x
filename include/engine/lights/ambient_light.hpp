// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/lights/light.hpp"

#include <memory>

namespace engine {

/**
 * @brief A light that gets emitted in all directions.
 */
class AmbientLight : public Light {
public:
    /**
     * @brief Constructs a new AmbientLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     */
    AmbientLight(Color color, float intensity) : Light(color, intensity) {
        SetName("ambient light");
    }

    /**
     * @brief Creates a new AmbientLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     * @return A shared pointer to the created AmbientLight.
     */
    [[nodiscard]] static auto Create(Color color = {0xffffff}, float intensity = 1.0f) {
        return std::make_shared<AmbientLight>(color, intensity);
    }

    /**
     * @brief Retrieves the type of the light.
     *
     * @return LightType::Ambient.
     */
    [[nodiscard]] auto Type() const -> LightType override {
        return LightType::AmbientLight;
    }

    /**
     * @brief Default destructor.
     */
    ~AmbientLight() override = default;
};

}