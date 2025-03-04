// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/arrow.hpp"

#include "engine/core/geometry.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/nodes/mesh.hpp"

namespace engine {

Arrow::Arrow(const Vector3& direction, const Vector3& origin, float length) {
    using enum GeometryAttributeType;
    using enum GeometryPrimitiveType;

    auto material = FlatMaterial::Create(0xFF0000);
    auto line = Mesh::Create(Geometry::Create({
        0, 0, 0,
        0, 0, 1
    }), material);
    line->GetGeometry()->SetName("directional light line");
    line->GetGeometry()->SetAttribute({Position, 3});
    line->GetGeometry()->primitive = Lines;
    line->LookAt(1.0f);
    Add(line);
}

}