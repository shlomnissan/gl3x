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
 * @brief A material for drawing geometries in a flat-shaded mode.
 * This material is not affected by lights.
 */
class ENGINE_EXPORT FlatMaterial : public Material {
public:
    /**
     * @brief Structure to hold the parameters for the FlatMaterial.
     */
    struct Parameters {
        /// @brief The base color of the material.
        Color color {};
        /// @brief Optional texture to be applied to the material.
        std::shared_ptr<Texture> texture {nullptr};
    };

    /**
     * @brief Constructs a FlatMaterial with the provided parameters.
     *
     * @param params A Parameters struct containing the color and optional texture.
     */
    explicit FlatMaterial(const Parameters& params) : params_(params) {}

    /**
     * @brief Creates a shared pointer to a default-constructed object.
     *
     * @param params A Parameters struct containing the color and optional texture.
     * @return std::shared_ptr<FlatMaterial> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create(const Parameters& params) {
        return std::make_shared<FlatMaterial>(params);
    }

private:
    /// @brief The parameters of the material, including color and optional texture.
    Parameters params_;
};

}