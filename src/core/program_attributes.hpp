// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/nodes/scene.hpp"

#include "materials/material.hpp"

#include <string>

namespace engine {

struct ProgramAttributes {
    MaterialType type;

    size_t directional_lights = 0;
    size_t point_lights = 0;
    size_t spot_lights = 0;

    bool color {false};
    bool texture_map {false};
    bool lights {false};

    ProgramAttributes(const Material* material, const Scene* scene);

    auto MaterialPermutationHash() const -> std::string;
};

}