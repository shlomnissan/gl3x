/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/arrow.hpp"

#include "gleam/geometries/cone_geometry.hpp"
#include "gleam/geometries/geometry.hpp"
#include "gleam/materials/unlit_material.hpp"
#include "gleam/nodes/mesh.hpp"

namespace gleam {

Arrow::Arrow(const Parameters& params) {
    const auto material = UnlitMaterial::Create(params.color);
    const auto cone_height = 0.1f;
    const auto cone = Mesh::Create(ConeGeometry::Create({
        .radius = 0.03f,
        .height = cone_height
    }), material);
    cone->TranslateZ(params.length - cone_height / 2.0f);
    cone->RotateX(math::DegToRad(90.0f));
    Add(cone);

    const auto geometry = Geometry::Create({
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, params.length - cone_height
    });
    geometry->SetAttribute({VertexAttributeType::Position, 3});
    geometry->primitive = GeometryPrimitiveType::Lines;
    Add(Mesh::Create(geometry, material));

    SetOrigin(params.origin);
    SetDirection(params.direction);
}

auto Arrow::SetDirection(const Vector3& direction) -> void {
    if (direction.LengthSquared() == 0.0f) return;
    LookAt(GetWorldPosition() + Normalize(direction));
}

auto Arrow::SetOrigin(const Vector3& origin) -> void {
    transform.SetPosition(origin);
}

}