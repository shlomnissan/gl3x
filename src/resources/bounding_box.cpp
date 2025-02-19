// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/bounding_box.hpp"

#include "engine/materials/flat_material.hpp"

#include <vector>

namespace engine {

BoundingBox::BoundingBox(const Box3& box, const Color& color) {
    auto mesh = Mesh::Create(CreateGeometry(box), FlatMaterial::Create(color));
    Add(mesh);
}

auto BoundingBox::CreateGeometry(const Box3& box) const -> std::shared_ptr<Geometry> {
    auto vertices = std::vector<float> {
        box.Max().x, box.Max().y, box.Max().z,
        box.Min().x, box.Max().y, box.Max().z,
        box.Min().x, box.Min().y, box.Max().z,
        box.Max().x, box.Min().y, box.Max().z,
        box.Max().x, box.Max().y, box.Min().z,
        box.Min().x, box.Max().y, box.Min().z,
        box.Min().x, box.Min().y, box.Min().z,
        box.Max().x, box.Min().y, box.Min().z
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