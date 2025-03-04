// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/bounding_plane.hpp"

#include "engine/materials/flat_material.hpp"
#include "engine/nodes/mesh.hpp"

#include <vector>

namespace engine {

BoundingPlane::BoundingPlane(const Plane& plane, float size, const Color& color) {
    auto wireframe_material = FlatMaterial::Create(color);
    wireframe_material->wireframe = true;
    wireframe_material->two_sided = true;
    Add(Mesh::Create(
        CreateWireframeGeometry(plane, size),
        wireframe_material
    ));

    auto solid_material = FlatMaterial::Create(color);
    solid_material->opacity = 0.2f;
    solid_material->transparent = true;
    Add(Mesh::Create(
        CreateSolidGeometry(plane, size),
        solid_material
    ));
}

auto BoundingPlane::CreateWireframeGeometry(
    const Plane& plane,
    float size
) const -> std::shared_ptr<Geometry> {
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
    return geometry;
}

auto BoundingPlane::CreateSolidGeometry(
    const Plane& plane,
    float size
) const -> std::shared_ptr<Geometry> {
    auto geometry = Geometry::Create({
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
   });
   geometry->SetAttribute({GeometryAttributeType::Position, 3});
   return geometry;
}

}