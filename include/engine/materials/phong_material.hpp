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
 * @brief A material for drawing geometries using the Blinn-Phong shading model.
 *
 * PhongMaterial is based on the Blinn-Phong shading model, a simple, non-physically based model used
 * to calculate the reflectance of surfaces. It supports both a solid color and a texture map for
 * rendering geometries.
 */
class ENGINE_EXPORT PhongMaterial :
    public virtual Material,
    public MaterialWithColor,
    public MaterialWithTextureMap
{
public:
    /**
     * @brief Constructs a PhongMaterial with a default white color and no texture.
     */
    explicit PhongMaterial() :
      MaterialWithColor(Color {1.0f, 1.0f, 1.0f}),
      MaterialWithTextureMap(nullptr) {}

    /**
     * @brief Retrieves the type of the material.
     *
     * @return The type of the material as `MaterialType::kPhongMaterial`.
     */
    auto Type() const -> MaterialType override {
        return MaterialType::kPhongMaterial;
    }

    /**
     * @brief Creates a new instance of PhongMaterial.
     *
     * @return A `std::shared_ptr` to a new instance of PhongMaterial.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<PhongMaterial>();
    }
};

}