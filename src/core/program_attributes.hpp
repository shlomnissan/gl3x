/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/nodes/mesh.hpp"
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

    bool alpha_map {false};
    bool color {false};
    bool flat_shaded {false};
    bool fog {false};
    bool instancing {false};
    bool texture_map {false};
    bool two_sided {false};

    ProgramAttributes(Mesh* mesh, const LightsCounter& lights, const Scene* scene);
};

}