/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx/nodes/renderable.hpp"
#include "vglx/nodes/scene.hpp"

#include <cstdint>
#include <string_view>
#include <utility>

namespace vglx {

struct ProgramAttributes {
    struct LightsCounter {
        uint8_t directional {0};
        uint8_t point {0};
        uint8_t spot {0};
    };

    std::size_t key {0};

    MaterialType type;

    // Used to store shader source code for shader materials
    std::string_view vertex_shader;
    std::string_view fragment_shader;

    uint8_t num_lights {0};

    bool albedo_map {false};
    bool alpha_map {false};
    bool color {false};
    bool flat_shaded {false};
    bool fog {false};
    bool instancing {false};
    bool normal_map {false};
    bool tangent {false};
    bool two_sided {false};
    bool vertex_color {false};

    ProgramAttributes(
        Renderable* renderable,
        const LightsCounter& lights,
        const Scene* scene
    );
};

}