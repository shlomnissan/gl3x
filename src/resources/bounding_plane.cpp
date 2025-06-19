/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/resources/bounding_plane.hpp"

#include "gleam/materials/flat_material.hpp"
#include "gleam/nodes/mesh.hpp"

#include <vector>

namespace gleam {

BoundingPlane::BoundingPlane(const Plane& plane, float size, const Color& color) {
    CreateWireframeMesh(color);
    CreateSolidMesh(color);
    SetScale({size * 0.5f, size * 0.5f, size});
    LookAt(plane.normal);
    TranslateZ(-plane.distance);
}

auto BoundingPlane::CreateWireframeMesh(const Color& color) -> void {
    auto geometry = Geometry::Create({
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         0.0f,  0.0f, 0.0f
    });
    geometry->SetAttribute({GeometryAttributeType::Position, 3});

    auto wireframe_material = FlatMaterial::Create(color);
    wireframe_material->wireframe = true;
    wireframe_material->two_sided = true;

    Add(Mesh::Create(geometry, wireframe_material));
}

auto BoundingPlane::CreateSolidMesh(const Color& color) -> void {
    auto geometry = Geometry::Create({
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    });

    geometry->SetAttribute({GeometryAttributeType::Position, 3});

    auto solid_material = FlatMaterial::Create(color);
    solid_material->opacity = 0.2f;
    solid_material->transparent = true;

    Add(Mesh::Create(geometry, solid_material));
}

}