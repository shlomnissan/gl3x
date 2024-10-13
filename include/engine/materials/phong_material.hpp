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
class ENGINE_EXPORT PhongMaterial :
    public virtual Material,
    public MaterialWithColor,
    public MaterialWithTextureMap
{
public:
    explicit PhongMaterial() :
      MaterialWithColor(Color {1.0f, 1.0f, 1.0f}),
      MaterialWithTextureMap(nullptr) {}

    auto Type() const -> MaterialType override {
        return MaterialType::kPhongMaterial;
    }

    auto Version() const -> double override {
        return 1.0;
    }

    [[nodiscard]] static auto Create() {
        return std::make_shared<PhongMaterial>();
    }
};

}