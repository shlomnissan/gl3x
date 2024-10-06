// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/color.hpp"

#include "materials/material.hpp"
#include "textures/texture.hpp"

#include <memory>

namespace engine {

/**
 * @brief A material for drawing geometries using the non-physically based
 * Blinn-Phong model for calculating reflectance.
 */
class ENGINE_EXPORT PhongMaterial : public Material {
public:
    /**
     * @brief Structure to hold the parameters for the PhongMaterial.
     */
    struct Parameters {
        /// @brief The base color of the material.
        Color color {};
        /// @brief Optional texture to be applied to the material.
        std::shared_ptr<Texture> texture {nullptr};
    };

    /**
     * @brief Constructs a PhongMaterial with the provided parameters.
     *
     * @param params A Parameters struct containing the color and optional texture.
     */
    explicit PhongMaterial(const Parameters& params) : params_(params) {
        SetName("Phong Material");
    }

    /**
     * @brief Returns the type of material.
     *
     * @return MaterialType an enum value representing the material type.
     */
    auto Type() const -> MaterialType override {
        return MaterialType::kPhongMaterial;
    }

    /**
     * @brief Creates a shared pointer to a default-constructed object.
     *
     * @param params A Parameters struct containing the color and optional texture.
     * @return std::shared_ptr<PhongMaterial> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<PhongMaterial>(params);
    }

private:
    /// @brief The parameters of the material, including color and optional texture.
    Parameters params_;
};

}