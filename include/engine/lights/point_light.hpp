// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/lights/light.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/nodes/mesh.hpp"

#include <memory>

namespace engine {

/**
 * @brief A light that gets emitted from a single point in all directions.
 */
class PointLight : public Light {
public:
    /// @brief The amount the light dims along the distance of the light.
    float decay {2.0f};

    /// @brief Maximum range of the light.
    float distance {0.0f};

    /// @brief The size of the debug mesh used to visualize the position of the light.
    float debug_mesh_size {0.25f};

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
        return LightType::PointLight;
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
    ~PointLight() override = default;

private:
    /// @brief The debug mesh used to visualize the position of the light.
    std::shared_ptr<Mesh> debug_mesh_sphere_;

    /// @brief The material used for the debug mesh.
    std::shared_ptr<FlatMaterial> debug_mesh_material_;

    /**
     * @brief Creates the debug mesh and material for the light.
     */
    auto CreateDebugMesh() -> void;
};

}