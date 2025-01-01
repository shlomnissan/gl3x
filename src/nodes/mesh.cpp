// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/nodes/mesh.hpp"

namespace engine {

Mesh::Mesh(
  std::shared_ptr<Geometry> geometry,
  std::shared_ptr<Material> material
) : geometry_(geometry), material_(material) {}

}