// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/materials/material.hpp"
#include "engine/math/color.hpp"
#include "engine/textures/texture_2d.hpp"

#include <memory>

namespace engine {

/**
 * @brief A material for drawing geometries without the influence of lighting.
 */
class ENGINE_EXPORT FlatMaterial : public Material {
public:
    /// @brief The color of the material.
    Color color = 0xFFFFFF;

    /// @brief The texture map to apply to the geometry.
    std::shared_ptr<Texture2D> texture_map = nullptr;

    /**
     * @brief Constructs a FlatMaterial with a specified color.
     *
     * @param color The color of the material.
     */
    explicit FlatMaterial(const Color& color) : color(color) {}

    /**
     * @brief Retrieves the type of the material.
     *
     * @return The type of the material as `MaterialType::FlatMaterial`.
     */
    auto Type() const -> MaterialType override {
        return MaterialType::FlatMaterial;
    }

    /**
     * @brief Creates a new instance of FlatMaterial.
     *
     * @return A `std::shared_ptr` to a new instance of FlatMaterial.
     */
    [[nodiscard]] static auto Create(const Color& color = 0xFFFFFF) {
        return std::make_shared<FlatMaterial>(color);
    }
};

}