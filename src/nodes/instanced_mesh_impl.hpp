/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/nodes/instanced_mesh.hpp"

namespace gleam {

struct InstancedMesh::Impl {
    unsigned int colors_buff_id = 0;
    unsigned int transforms_buff_id = 0;
    bool colors_touched {true};
    bool transforms_touched {true};
};

}