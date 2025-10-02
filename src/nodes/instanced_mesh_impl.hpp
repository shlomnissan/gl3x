/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x/math/box3.hpp"
#include "gl3x/math/sphere.hpp"
#include "gl3x/nodes/instanced_mesh.hpp"

namespace gl3x {

struct InstancedMesh::Impl {
    Box3 bounding_box {};
    Sphere bounding_sphere {};
    unsigned int colors_buff_id = 0;
    unsigned int transforms_buff_id = 0;
    bool bounding_box_touched {true};
    bool bounding_sphere_touched {true};
    bool colors_touched {true};
    bool transforms_touched {true};
};

}