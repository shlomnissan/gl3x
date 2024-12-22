// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/nodes/scene.hpp"
#include "engine/materials/material.hpp"

#include <string>

namespace engine {

struct ProgramAttributes {
    MaterialType type;

    int directional_lights = 0;
    int point_lights = 0;
    int spot_lights = 0;

    bool fog {false};
    bool color {false};
    bool texture_map {false};
    bool lights {false};

    ProgramAttributes(const Material* material, const Scene* scene);

    auto ProgramPermutationHash() const -> std::string;
};

}