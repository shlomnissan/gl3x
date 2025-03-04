// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/arrow.hpp"

#include "engine/core/geometry.hpp"
#include "engine/geometries/cone_geometry.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/nodes/mesh.hpp"

namespace engine {

Arrow::Arrow(const Vector3& direction, const Vector3& origin, const Color& color, float length) {
    const auto material = FlatMaterial::Create(color);
    const auto cone_height = 0.1f;

    auto cone = Mesh::Create(ConeGeometry::Create({
        .radius = 0.03f,
        .height = cone_height
    }), material);
    cone->TranslateZ(length - cone_height);
    cone->RotateX(math::DegToRad(90.0f));
    Add(cone);

    auto line = Mesh::Create(Geometry::Create({
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, length - cone_height
    }), material);
    line->GetGeometry()->SetAttribute({GeometryAttributeType::Position, 3});
    line->GetGeometry()->primitive = GeometryPrimitiveType::Lines;
    Add(line);

    transform.SetPosition(origin);
    LookAt(Normalize(direction));
}

}