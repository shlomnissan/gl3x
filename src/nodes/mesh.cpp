/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/mesh.hpp"

namespace gleam {

Mesh::Mesh(
    std::shared_ptr<Geometry> geometry,
    std::shared_ptr<Material> material
) : geometry(geometry), material(material) {}

}