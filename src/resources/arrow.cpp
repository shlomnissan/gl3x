// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/arrow.hpp"

#include "engine/core/geometry.hpp"
#include "engine/geometries/cone_geometry.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/nodes/mesh.hpp"

namespace engine {

Arrow::Arrow(const Parameters& params) {
    const auto material = FlatMaterial::Create(params.color);
    const auto cone_height = 0.1f;

    auto cone = Mesh::Create(ConeGeometry::Create({
        .radius = 0.03f,
        .height = cone_height
    }), material);
    cone->TranslateZ(params.length - cone_height);
    cone->RotateX(math::DegToRad(90.0f));
    Add(cone);

    auto geometry = Geometry::Create({
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, params.length - cone_height
    });
    geometry->SetAttribute({GeometryAttributeType::Position, 3});
    geometry->primitive = GeometryPrimitiveType::Lines;
    auto line = Mesh::Create(geometry, material);
    Add(line);

    SetOrigin(params.origin);
    SetDirection(params.direction);
}

auto Arrow::SetDirection(const Vector3& direction) -> void {
    if (direction.LengthSquared() == 0.0f) return;
    LookAt(Normalize(direction));
}

auto Arrow::SetOrigin(const Vector3& origin) -> void {
    transform.SetPosition(origin);
}

}