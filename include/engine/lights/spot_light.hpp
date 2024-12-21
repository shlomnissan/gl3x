// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/lights/light.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/math/utilities.hpp"
#include "engine/nodes/mesh.hpp"

#include <memory>

namespace engine {

/**
 * @brief This light gets emittedin one direction along a cone.
 */
class SpotLight : public Light {
public:
    /// @brief The angle of the light cone.
    float cutoff_angle {math::pi / 3.0f};

    /// @brief The amount the light dims along the distance of the light.
    float decay {1.0f};

    /// @brief Maximum range of the light.
    float distance {0.0f};

    /**
     * @brief Construct a new SpotLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     */
    SpotLight(Color color, float intensity) : Light(color, intensity) {
        SetName("spot light");
    }

    /**
     * @brief Creates a new SpotLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     * @return A shared pointer to the created SpotLight.
     */
    [[nodiscard]] static auto Create(Color color = {0xffffff}, float intensity = 1.0f) {
        return std::make_shared<SpotLight>(color, intensity);
    }

    /**
     * @brief Retrieves the type of the light.
     *
     * @return LightType::Spot.
     */
    [[nodiscard]] auto Type() const -> LightType override {
        return LightType::Spot;
    }

    /**
     * @brief Enables or disables the debug mode for the light.
     *
     * @param is_debug_mode A flag indicating whether debug mode should be enabled.
     */
    auto SetDebugMode(bool is_debug_mode) -> void override;

    /**
     * @brief Invoked when the node is updated.
     *
     * @param delta The time in seconds since the last update.
     */
    auto Update(float delta) -> void override;

    /**
     * @brief Default destructor.
     */
    ~SpotLight() override = default;

private:
    /// @brief The debug mesh used to visualize the position of the light.
    std::shared_ptr<Mesh> debug_mesh_cone_;

    /// @brief The material of the debug mesh.
    std::shared_ptr<FlatMaterial> debug_mesh_material_;

    /**
     * @brief Creates a debug mesh to visualize the the light.
     */
    auto CreateDebugMesh() -> void;
};

}