// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/core/geometry.hpp"
#include "engine/math/vector3.hpp"
#include "engine/nodes/mesh.hpp"

#include <limits>

namespace engine {

Mesh::Mesh(
    std::shared_ptr<Geometry> geometry,
    std::shared_ptr<Material> material
) : geometry(geometry), material(material) {}

}