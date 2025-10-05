/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/nodes/grid.hpp"

#include "gl3x/materials/unlit_material.hpp"
#include "gl3x/nodes/mesh.hpp"

#include <vector>

namespace gl3x {

Grid::Grid(const Parameters& params) {
    const auto center = params.divisions / 2;
    const auto step = params.size / params.divisions;
    const auto half_size = params.size / 2;
    auto vertices = std::vector<float> {};
    auto k = -half_size;
    for (auto i = 0, j = 0; i <= params.divisions; i++) {
        vertices.insert(vertices.end(), {
           -half_size, 0.0f, k,
            half_size, 0.0f, k,
            k, 0.0f, -half_size,
            k, 0.0f, half_size
        });
        k += step;
    }

    using enum VertexAttributeType;

    auto geometry = Geometry::Create(vertices);
    geometry->SetAttribute({.type = Position, .item_size = 3});
    geometry->primitive = GeometryPrimitiveType::Lines;
    geometry->SetName("grid");

    Add(Mesh::Create(geometry, UnlitMaterial::Create(params.color)));
}

}