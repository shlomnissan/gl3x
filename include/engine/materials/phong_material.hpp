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
    public MaterialWithColor
{
public:
    explicit PhongMaterial() :
      MaterialWithColor(Color {1.0f, 1.0f, 1.0f}) {
        SetName("Phong Material");
    }

    auto Type() const -> MaterialType override {
        return MaterialType::kPhongMaterial;
    }

    [[nodiscard]] static auto Create() {
        return std::make_shared<PhongMaterial>();
    }
};

}