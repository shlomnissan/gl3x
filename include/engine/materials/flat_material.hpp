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
 *
 * FlatMaterial renders objects without the influence of lighting. The material can be assigned a solid color
 * and optionally a texture map to apply onto the surface. This makes it ideal for simple, unlit geometries.
 */
class ENGINE_EXPORT FlatMaterial : public Material {
public:
    /// @brief The color of the material.
    Color color = {1.0f, 1.0f, 1.0f, 1.0f};

    /// @brief The texture map to apply to the geometry.
    std::shared_ptr<Texture2D> texture_map = nullptr;

    /**
     * @brief Constructs a FlatMaterial with default values.
     */
    FlatMaterial() = default;

    /**
     * @brief Retrieves the type of the material.
     *
     * @return The type of the material as `MaterialType::kFlatMaterial`.
     */
    auto Type() const -> MaterialType override {
        return MaterialType::kFlatMaterial;
    }

    /**
     * @brief Creates a new instance of FlatMaterial.
     *
     * @return A `std::shared_ptr` to a new instance of FlatMaterial.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<FlatMaterial>();
    }
};

}