// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/bounding_plane.hpp"

#include "engine/materials/flat_material.hpp"
#include "engine/nodes/mesh.hpp"

#include <vector>

namespace engine {

BoundingPlane::BoundingPlane(const Plane& plane, float size, const Color& color) {
    Add(Mesh::Create(CreateGeometry(plane, size), FlatMaterial::Create(color)));
}

auto BoundingPlane::CreateGeometry(
    const Plane& plane,
    float size
) const -> std::shared_ptr<Geometry> {
    // TODO: generate geometry
    return std::make_shared<Geometry>();
}

}