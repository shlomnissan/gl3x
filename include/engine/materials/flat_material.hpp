// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "materials/material.hpp"

#include <memory>

namespace engine {

/**
 * @brief A material for drawing geometries in a flat-shaded mode.
 * This material is not affected by lights.
 */
class ENGINE_EXPORT FlatMaterial : public Material {
public:
    /**
     * @brief Creates a shared pointer to a default-constructed object.
     *
     * @return std::shared_ptr<FlatMaterial> A shared pointer to the newly created object.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<FlatMaterial>();
    }
};

}