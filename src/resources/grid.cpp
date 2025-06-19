/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/resources/grid.hpp"

#include "gleam/materials/flat_material.hpp"
#include "gleam/nodes/mesh.hpp"

#include <vector>

namespace gleam {

Grid::Grid(const Parameters& params) {
    const auto center = params.divisions / 2;
    const auto step = params.size / params.divisions;
    const auto half_size = params.size / 2;

    auto vertices = std::vector<float> {};

    auto k = -half_size;
    for (auto i = 0, j = 0; i <= params.divisions; i++) {
        vertices.emplace_back(-half_size);
        vertices.emplace_back(0.0f);
        vertices.emplace_back(k);
        vertices.emplace_back(half_size);
        vertices.emplace_back(0.0f);
        vertices.emplace_back(k);

        vertices.emplace_back(k);
        vertices.emplace_back(0.0f);
        vertices.emplace_back(-half_size);
        vertices.emplace_back(k);
        vertices.emplace_back(0.0f);
        vertices.emplace_back(half_size);

        k += step;
    }

    auto geometry = Geometry::Create(vertices);
    geometry->SetAttribute({
        .type = GeometryAttributeType::Position,
        .item_size = 3
    });
    geometry->primitive = GeometryPrimitiveType::Lines;
    geometry->SetName("grid");

    Add(Mesh::Create(geometry, FlatMaterial::Create(params.color)));
}

}