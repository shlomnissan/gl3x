// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/scene/scene.hpp"

#include "materials/material.hpp"

#include <string>

namespace engine {

struct ProgramAttributes {
    MaterialType type;

    size_t num_directional_lights = 0;
    size_t num_point_lights = 0;
    size_t num_spot_lights = 0;

    bool color {false};
    bool texture_map {false};
    bool lights {false};

    ProgramAttributes(const Material* material, const Scene* scene);

    auto MaterialPermutationHash() const -> std::string;
};

}