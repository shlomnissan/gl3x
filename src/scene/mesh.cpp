// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/scene/mesh.hpp"

namespace engine {

Mesh::Mesh(
  std::shared_ptr<Geometry> geometry,
  std::shared_ptr<Material> material
) : geometry_(geometry), material_(material) {}

}