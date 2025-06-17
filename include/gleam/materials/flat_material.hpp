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
 * auto material = gleam::FlatMaterial::Create(0x049EF4);
 * material->texture_map = texture;
 *
 * auto mesh = gleam::Mesh::Create(geometry, material);
 * scene->Add(mesh);
 * @endcode
 *
 * @ingroup MaterialsGroup
 */
class GLEAM_EXPORT FlatMaterial : public Material {
public:
    /// @brief Color of the material.
    Color color = 0xFFFFFF;

    /// @brief Texture map that may optionally include an alpha channel.
    std::shared_ptr<Texture2D> texture_map = nullptr;

    /**
     * @brief Constructs a FlatMaterial object.
     *
     * @param color Color of the material.
     */
    explicit FlatMaterial(const Color& color) : color(color) {}

    /**
     * @brief Creates a shared pointer to a FlatMaterial object.
     *
     * @param color Color of the material.
     * @return std::shared_ptr<FlatMaterial>
     */
    [[nodiscard]] static auto Create(const Color& color = 0xFFFFFF) {
        return std::make_shared<FlatMaterial>(color);
    }

    /**
     * @brief Returns material type.
     *
     * @return MaterialType::FlatMaterial
     */
    auto GetType() const -> MaterialType override {
        return MaterialType::FlatMaterial;
    }
};

}