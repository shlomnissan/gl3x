// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/lights/light.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/nodes/mesh.hpp"

#include <memory>

namespace engine {

/**
 * @brief Represents a light that gets emitted from a single point in all
 * directions. A common use case for this is to replicate the light emitted
 * from a bare lightbulb.
 *
 * @code
 * auto point_light = PointLight::Create({
 *   .color = 0xFFFFFF,
 *   .intensity = 1.0f,
 *   .attenuation = {
 *     .base = 1.0f,
 *     .linear = 0.0f,
 *     .quadratic = 0.0f
 *   }
 * });
 * @endcode
 *
 * @ingroup LightsGroup
 */
class ENGINE_EXPORT PointLight : public Light {
public:
    /// @brief Parameters for constructing a PointLight object.
    struct Parameters {
        Color color; ///< Light color.
        float intensity; ///< Light intensity.
        Attenuation attenuation; ///< Light attenuation properties.
    };

    /// @brief Light attenuation properties.
    Attenuation attenuation;

    /**
     * @brief Constructs a PointLight object.
     *
     * @param params PointLight::Parameters
     */
    PointLight(const Parameters& params) :
        Light(params.color, params.intensity),
        attenuation(params.attenuation)
    {
        SetName("point light");
    }

    /**
     * @brief Creates a shared pointer to an PointLight object.
     *
     * @param params PointLight::Parameters
     * @return std::shared_ptr<PointLight>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<PointLight>(params);
    }

    /**
     * @brief Returns light type.
     *
     * @return LightType::PointLight
     */
    [[nodiscard]] auto Type() const -> LightType override {
        return LightType::PointLight;
    }

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

private:
    /// @brief Mesh used to visualize the light's position in debug mode.
    std::shared_ptr<Mesh> debug_mesh_sphere_;

    /// @brief Material used for rendering debug meshes.
    std::shared_ptr<FlatMaterial> debug_mesh_material_;

    /**
     * @brief Creates the debug mesh for visualizing the light's position.
     */
    auto CreateDebugMesh() -> void;

    /**
     * @brief Updates the debug mesh to reflect the current light state.
     */
    auto UpdateDebugMesh() -> void;
};

}