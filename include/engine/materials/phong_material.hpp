// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/materials/material.hpp"
#include "engine/math/color.hpp"
#include "engine/textures/texture.hpp"

#include <memory>

namespace engine {

/**
 * @brief A material for drawing geometries using the Blinn-Phong shading model.
 *
 * PhongMaterial is based on the Blinn-Phong shading model, a simple, non-physically based model used
 * to calculate the reflectance of surfaces. It supports both a solid color and a texture map for
 * rendering geometries.
 */
class ENGINE_EXPORT PhongMaterial : public Material {
public:
    /// @brief The color of the material.
    Color color = 0xFFFFFF;

    /// @brief The specular color of the material.
    Color specular = 0x191919;

    /// @brief The shininess of the material.
    float shininess = 32.0f;

    /// @brief The texture map to apply to the geometry.
    std::shared_ptr<Texture2D> texture_map = nullptr;

    /**
     * @brief Constructs a FlatMaterial with a specified color.
     *
     * @param color The color of the material.
     */
    explicit PhongMaterial(const Color& color) : color(color) {}

    /**
     * @brief Retrieves the type of the material.
     *
     * @return The type of the material as `MaterialType::PhongMaterial`.
     */
    auto Type() const -> MaterialType override {
        return MaterialType::PhongMaterial;
    }

    /**
     * @brief Creates a new instance of PhongMaterial.
     *
     * @return A `std::shared_ptr` to a new instance of PhongMaterial.
     */
    [[nodiscard]] static auto Create(const Color& color = 0xFFFFFF) {
        return std::make_shared<PhongMaterial>(color);
    }
};

}