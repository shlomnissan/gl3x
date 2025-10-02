/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/materials/material.hpp"
#include "gl3x/math/color.hpp"
#include "gl3x/textures/texture_2d.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Represents a material for shiny surfaces with specular highlights.
 *
 * This material implements the Blinn-Phong model for calculating reflectance.
 * It is suitable for rendering glossy or metallic surfaces that require
 * highlights and simulate light interaction.
 *
 * @code
 * auto material = gl3x::PhongMaterial::Create(0x049EF4);
 * material->specular = {0.3f, 0.3, 0.3f}
 * material->shininess = 32.0f;
 * material->albedo_map = texture;
 *
 * auto mesh = gl3x::Mesh::Create(geometry, material);
 * scene->Add(mesh);
 * @endcode
 *
 * @ingroup MaterialsGroup
 */
class GL3X_EXPORT PhongMaterial : public Material {
public:
    /// @brief Color of the material.
    Color color = 0xFFFFFF;

    /// @brief Specular color of the material.
    Color specular = 0x111111;

    /// @brief How shiny the specular highlight is; a higher value gives a sharper highlight.
    float shininess = 32.0f;

    /// @brief Albedo (base color) map, optionally containing an alpha channel.
    std::shared_ptr<Texture2D> albedo_map = nullptr;

    /// @brief Alpha map that controls the opacity across the surface.
    std::shared_ptr<Texture2D> alpha_map = nullptr;

    /// @brief Normal map that perturbs surface normals for detailed shading.
    std::shared_ptr<Texture2D> normal_map = nullptr;

    /**
     * @brief Constructs a PhongMaterial object.
     *
     * @param color Color of the material.
     */
    explicit PhongMaterial(const Color& color) : color(color) {}

    /**
     * @brief Creates a shared pointer to a PhongMaterial object.
     *
     * @param color Color of the material.
     * @return std::shared_ptr<PhongMaterial>
     */
    [[nodiscard]] static auto Create(const Color& color = 0xFFFFFF) {
        return std::make_shared<PhongMaterial>(color);
    }

    /**
     * @brief Returns material type.
     *
     * @return MaterialType::PhongMaterial
     */
    auto GetType() const -> MaterialType override {
        return MaterialType::PhongMaterial;
    }
};

}