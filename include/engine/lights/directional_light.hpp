// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/lights/light.hpp"

#include <memory>

namespace engine {

/**
 * @brief A light that gets emitted in a specific direction.
 *
 * This light behaves as though it is infinitely far away, producing parallel
 * rays. Commonly used to simulate daylight, as the sun is far enough away
 * that its position can be considered infinite, and all light rays are parallel.
 */
class DirectionalLight : public Light {
public:
    /**
     * @brief Creates a new DirectionalLight instance.
     *
     * @return A shared pointer to the created DirectionalLight.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<DirectionalLight>();
    }

    /**
     * @brief Retrieves the type of the light.
     *
     * @return LightType::Directional.
     */
    auto Type() const -> LightType override {
        return LightType::Directional;
    }
};

}