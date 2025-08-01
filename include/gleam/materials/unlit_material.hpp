/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/materials/material.hpp"
#include "gleam/math/color.hpp"
#include "gleam/textures/texture_2d.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Represents a material for surfaces that are not affected by lights.
 *
 * This material is used to render objects with uniform color or texture,
 * without any lighting calculations. It is ideal for UI elements, 2D overlays,
 * or wireframes where shading is not desired.
 *
 * @code
 * auto material = gleam::UnlitMaterial::Create(0x049EF4);
 * material->albedo_map = texture;
 *
 * auto mesh = gleam::Mesh::Create(geometry, material);
 * scene->Add(mesh);
 * @endcode
 *
 * @ingroup MaterialsGroup
 */
class GLEAM_EXPORT UnlitMaterial : public Material {
public:
    /// @brief Color of the material.
    Color color = 0xFFFFFF;

    /// @brief Albedo (base color) map, optionally containing an alpha channel.
    std::shared_ptr<Texture2D> albedo_map = nullptr;

    /// @brief Alpha map that controls the opacity across the surface.
    std::shared_ptr<Texture2D> alpha_map = nullptr;

    /**
     * @brief Constructs a UnlitMaterial object.
     *
     * @param color Color of the material.
     */
    explicit UnlitMaterial(const Color& color) : color(color) {}

    /**
     * @brief Creates a shared pointer to a UnlitMaterial object.
     *
     * @param color Color of the material.
     * @return std::shared_ptr<UnlitMaterial>
     */
    [[nodiscard]] static auto Create(const Color& color = 0xFFFFFF) {
        return std::make_shared<UnlitMaterial>(color);
    }

    /**
     * @brief Returns material type.
     *
     * @return MaterialType::UnlitMaterial
     */
    auto GetType() const -> MaterialType override {
        return MaterialType::UnlitMaterial;
    }
};

}