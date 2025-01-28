// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine_export.h"
#include "engine/materials/material.hpp"
#include "engine/math/color.hpp"

namespace engine {

/**
 * @brief A material rendered with custom shaders.
 */
class ENGINE_EXPORT ShaderMaterial : public Material {
    /**
     * @brief Retrieves the type of the material.
     *
     * @return The type of the material as `MaterialType::ShaderMaterial`.
     */
    auto Type() const -> MaterialType override {
        return MaterialType::ShaderMaterial;
    }
};

}