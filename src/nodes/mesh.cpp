/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/core/geometry.hpp"
#include "gleam/math/vector3.hpp"
#include "gleam/nodes/mesh.hpp"

#include <limits>

namespace gleam {

Mesh::Mesh(
    std::shared_ptr<Geometry> geometry,
    std::shared_ptr<Material> material
) : geometry(geometry), material(material) {}

}