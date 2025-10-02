/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/nodes/bounding_box.hpp"

#include "gl3x/geometries/geometry.hpp"
#include "gl3x/materials/unlit_material.hpp"
#include "gl3x/nodes/mesh.hpp"

#include <vector>

namespace gleam {

namespace {

auto create_geometry(const Box3& box) {
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
        .type = VertexAttributeType::Position,
        .item_size = 3
    });

    return geometry;
}

}

BoundingBox::BoundingBox(const Box3& box, const Color& color) {
    Add(Mesh::Create(create_geometry(box), UnlitMaterial::Create(color)));
}

}