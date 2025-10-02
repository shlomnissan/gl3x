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
 * @brief Represents a material for 2D sprites.
 *
 * `SpriteMaterial` is a lightweight material optimized for rendering
 * camera-facing quads such as UI elements, particles, or font glyphs.
 * It supports a solid color, an optional albedo map, and an optional
 * alpha map for per-pixel transparency.
 *
 * Unlike physically-based or Phong materials, `SpriteMaterial` is
 * rendered without lighting by default, making it efficient for 2D
 * overlays and screen-space elements.
 *
 * @code
 * auto material = gl3x::SpriteMaterial::Create(0xFFFFFF);
 * material->albedo_map = texture;
 *
 * auto sprite = gl3x::Sprite::Create(material);
 * scene->Add(sprite);
 * @endcode
 *
 * @ingroup MaterialsGroup
 */
class GL3X_EXPORT SpriteMaterial : public Material {
public:
    /// @brief Color of the material.
    Color color = 0xFFFFFF;

    /// @brief Albedo (base color) map, optionally containing an alpha channel.
    std::shared_ptr<Texture2D> albedo_map = nullptr;

    /// @brief Alpha map that controls the opacity across the surface.
    std::shared_ptr<Texture2D> alpha_map = nullptr;

    /**
     * @brief Constructs a SpriteMaterial object.
     *
     * @param color Color of the material.
     */
    explicit SpriteMaterial(const Color& color): color(color) {
        transparent = true;
    }

    /**
     * @brief Creates a shared pointer to a SpriteMaterial object.
     *
     * @param color Color of the material.
     * @return std::shared_ptr<SpriteMaterial>
     */
    [[nodiscard]] static auto Create(const Color& color = 0xFFFFFF) {
        return std::make_shared<SpriteMaterial>(color);
    }

    /**
     * @brief Returns material type.
     *
     * @return MaterialType::SpriteMaterial
     */
    auto GetType() const -> MaterialType override {
        return MaterialType::SpriteMaterial;
    }
};

}