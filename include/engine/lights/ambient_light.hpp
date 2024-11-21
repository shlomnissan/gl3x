// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "lights/light.hpp"

#include <memory>

namespace engine {

/**
 * @brief A light that gets emitted in all directions.
 *
 * Ambient light is a type of light that gets emitted in all directions. It
 * is used to simulate the light that is scattered in the atmosphere, creating
 * a uniform lighting effect on all objects in the scene.
 */
class AmbientLight : public Light {
public:
    /**
     * @brief Constructs a new AmbientLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     */
    AmbientLight(Color color = {0xffffff}, float intensity = 1.0f) : Light(color, intensity) {
        SetName("Ambient Light");
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
        return LightType::Ambient;
    }

    /**
     * @brief Default destructor.
     */
    ~AmbientLight() override = default;
};

}