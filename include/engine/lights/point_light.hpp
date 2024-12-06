// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "lights/light.hpp"

#include <memory>

namespace engine {

/**
 * @brief A light that gets emitted from a single point in all directions.
 */
class PointLight : public Light {
public:
    /// @brief The amount the light dims along the distance of the light.
    float decay {1.0f};

    /// @brief Maximum range of the light.
    float distance {0.0f};

    /**
     * @brief Constructs a new PointLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     */
    PointLight(Color color, float intensity) : Light(color, intensity) {
        SetName("point light");
    }

    /**
     * @brief Creates a new PointLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     * @return A shared pointer to the created PointLight.
     */
    [[nodiscard]] static auto Create(Color color = {0xffffff}, float intensity = 1.0f) {
        return std::make_shared<PointLight>(color, intensity);
    }

    /**
     * @brief Retrieves the type of the light.
     *
     * @return LightType::Point.
     */
    [[nodiscard]] auto Type() const -> LightType override {
        return LightType::Point;
    }

    /**
     * @brief Default destructor.
     */
    ~PointLight() override = default;
};

}