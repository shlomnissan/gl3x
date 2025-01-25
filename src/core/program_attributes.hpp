// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine/materials/material.hpp"
#include "engine/nodes/scene.hpp"

#include "core/render_lists.hpp"

#include <string>

namespace engine {

struct ProgramAttributes {
    MaterialType type;

    int directional_lights = 0;
    int point_lights = 0;
    int spot_lights = 0;

    bool linear_fog {false};
    bool lights {false};
    bool texture_map {false};
    bool two_sided {false};

    ProgramAttributes(const Material* material, const RenderLists* render_lists, const Scene* scene);

    auto ProgramPermutationHash() const -> std::string;
};

}