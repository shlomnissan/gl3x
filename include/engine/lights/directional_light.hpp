// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "lights/light.hpp"

#include "engine/materials/flat_material.hpp"
#include "engine/math/vector3.hpp"
#include "engine/scene/mesh.hpp"

#include <memory>

namespace engine {

/**
 * @brief A light that gets emitted in a specific direction.
 */
class DirectionalLight : public Light {
public:
    /**
     * @brief The target node that the light is pointing towards.
     *
     * If this is not set, the light will always point towards the origin.
     */
    std::shared_ptr<Node> target {nullptr};

    /**
     * @brief Constructs a new DirectionalLight instance.
     *
     * @param color The color of the light.
     * @param intensity The intensity of the light.
     */
    DirectionalLight(Color color, float intensity) : Light(color, intensity) {
        SetName("directional light");
    }

    /**
     * @brief Creates a new DirectionalLight instance.
     *
    * @param color The color of the light.
     * @param intensity The intensity of the light.
     * @return A shared pointer to the created DirectionalLight.
     */
    [[nodiscard]] static auto Create(Color color = {0xffffff}, float intensity = 1.0f) {
        return std::make_shared<DirectionalLight>(color, intensity);
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
     * @brief Enables or disables the debug mode for the light.
     *
     * @param is_debug_mode A flag indicating whether debug mode should be enabled.
     */
    auto SetDebugMode(bool is_debug_mode) -> void override;

    /**
     * @brief Retrieves the direction of the light based on the light's target.
     *
     * @return The direction of the light.
     */
    [[nodiscard]] auto Direction() -> Vector3;

    /**
     * @brief Invoked when the node is updated.
     *
     * @param delta The time in seconds since the last update.
     */
    auto Update(float delta) -> void override;

    /**
     * @brief Default destructor.
     */
    ~DirectionalLight() override = default;

private:
    /// @brief The debug mesh used to visualize the direction of the light.
    std::shared_ptr<Mesh> debug_mesh_line_;
    /// @brief The debug mesh used to visualize the position of the light.
    std::shared_ptr<Mesh> debug_mesh_plane_;
    /// @brief The material used for the debug mesh.
    std::shared_ptr<FlatMaterial> debug_mesh_material_;

    auto CreateDebugMesh() -> void;
};

}