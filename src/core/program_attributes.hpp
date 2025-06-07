/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/materials/material.hpp"
#include "gleam/nodes/scene.hpp"

#include "core/render_lists.hpp"

#include <string_view>

namespace gleam {

struct ProgramAttributes {
    std::size_t key;

    MaterialType type;

    // Used to store shader source code for shader materials
    std::string_view vertex_shader;
    std::string_view fragment_shader;

    int directional_lights = 0;
    int point_lights = 0;
    int spot_lights = 0;

    bool color {false};
    bool fog {false};
    bool lights {false};
    bool texture_map {false};
    bool two_sided {false};
    bool flat_shaded {false};

    ProgramAttributes(const Material* material, const RenderLists* render_lists, const Scene* scene);
};

}