/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/materials/material.hpp"
#include "gleam/nodes/scene.hpp"

#include <string_view>
#include <utility>

namespace gleam {

struct ProgramAttributes {
    struct LightsCounter {
        unsigned int directional {0};
        unsigned int point {0};
        unsigned int spot {0};
    };

    std::size_t key {0};

    MaterialType type;

    // Used to store shader source code for shader materials
    std::string_view vertex_shader;
    std::string_view fragment_shader;

    unsigned int num_lights {0};

    bool color {false};
    bool fog {false};
    bool texture_map {false};
    bool two_sided {false};
    bool flat_shaded {false};

    ProgramAttributes(const Material* material, const LightsCounter& lights, const Scene* scene);
};

}