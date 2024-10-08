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
 * This material is not affected by lights.
 */
class ENGINE_EXPORT FlatMaterial :
    public virtual Material,
    public MaterialWithColor
{
public:
    explicit FlatMaterial() :
      MaterialWithColor(Color {1.0f, 1.0f, 1.0f}) {
        SetName("Flat Material");
    }

    auto Type() const -> MaterialType override {
        return MaterialType::kFlatMaterial;
    }

    [[nodiscard]] static auto Create() {
        return std::make_shared<FlatMaterial>();
    }
};

}