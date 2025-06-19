/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/resources/bounding_box.hpp"

#include "gleam/materials/flat_material.hpp"
#include "gleam/nodes/mesh.hpp"

#include <vector>

namespace gleam {

BoundingBox::BoundingBox(const Box3& box, const Color& color) {
    Add(Mesh::Create(CreateGeometry(box), FlatMaterial::Create(color)));
}

auto BoundingBox::CreateGeometry(const Box3& box) const -> std::shared_ptr<Geometry> {
    auto vertices = std::vector<float> {
        box.max.x, box.max.y, box.max.z,
        box.min.x, box.max.y, box.max.z,
        box.min.x, box.min.y, box.max.z,
        box.max.x, box.min.y, box.max.z,
        box.max.x, box.max.y, box.min.z,
        box.min.x, box.max.y, box.min.z,
        box.min.x, box.min.y, box.min.z,
        box.max.x, box.min.y, box.min.z
    };

    auto indices = std::vector<unsigned> {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    };

    auto geometry = Geometry::Create(vertices, indices);
    geometry->primitive = GeometryPrimitiveType::Lines;
    geometry->SetAttribute({
        .type = GeometryAttributeType::Position,
        .item_size = 3
    });

    return geometry;
}

}