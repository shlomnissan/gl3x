// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/lights/light.hpp"
#include "engine/math/vector3.hpp"

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
    /// @brief The target point that the light is directed towards.
    Vector3 target {0.0f};

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

    /**
     * @brief Overrides the update function to update the light debug geometry.
     *
     * @param delta The time in seconds since the last update.
     */
    auto Update(double delta) -> void override;

private:
    auto UpdateDebugMesh() -> void;
};

}