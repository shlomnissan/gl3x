/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/lights/light.hpp"
#include "gleam/materials/flat_material.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/nodes/mesh.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Represents a light that gets emitted in a specific direction. This
 * light will behave as though it is infinitely far away and the rays produced
 * from it are all parallel. The common use case for this is to simulate
 * daylight; the sun is far enough away that its position can be considered
 * to be infinite, and all light rays coming from it are parallel.
 *
 * @code
 * Add(DirectionalLight::Create({
 *   .color = 0xFFFFFF,
 *   .intensity = 1.0f,
 *   .target = nullptr
 * }));
 * @endcode
 *
 * When the target parameter is set to `nullptr` the light points to (0, 0, 0).
 *
 * @ingroup LightsGroup
 */
class GLEAM_EXPORT DirectionalLight : public Light {
public:
    /// @brief Parameters for constructing a DirectionalLight object.
    struct Parameters {
        Color color; ///< Light color.
        float intensity; ///< Light intensity.
        std::shared_ptr<Node> target; ///< Light target position.
    };

    /// @brief Node that the light is directed towards.
    std::shared_ptr<Node> target;

    /**
     * @brief Constructs a DirectionalLight object.
     *
     * @param params DirectionalLight::Parameters
     */
    explicit DirectionalLight(const Parameters& params) :
        Light(params.color, params.intensity),
        target(params.target)
    {
        SetName("directional light");
    }

    /**
     * @brief Creates a shared pointer to an DirectionalLight object.
     *
     * @param params DirectionalLight::Parameters
     * @return std::shared_ptr<DirectionalLight>
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<DirectionalLight>(params);
    }

    /**
     * @brief Returns light type.
     *
     * @return LightType::DirectionalLight
     */
    auto Type() const -> LightType override {
        return LightType::DirectionalLight;
    }

    /**
     * @brief Returns the direction vector of the light.
     *
     * Calculates and returns the normalized direction in which the directional
     * light is pointing. The direction is determined based on the light's
     * position and its target node.
     *
     * @return Vector3
     */
    [[nodiscard]] auto Direction() -> Vector3;

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
    /// @brief Mesh used to visualize the light's direction in debug mode.
    std::shared_ptr<Mesh> debug_mesh_line_;

    /// @brief Mesh used to visualize the light's area of effect in debug mode.
    std::shared_ptr<Mesh> debug_mesh_plane_;

    /// @brief Material used for rendering debug meshes.
    std::shared_ptr<FlatMaterial> debug_mesh_material_;

    /**
     * @brief Creates the debug mesh for visualizing the light's direction and area.
     */
    auto CreateDebugMesh() -> void;

    /**
     * @brief Updates the debug mesh to reflect the current light state.
     */
    auto UpdateDebugMesh() -> void;
};

}