// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/resources/grid.hpp"

#include "engine/core/geometry.hpp"
#include "engine/materials/flat_material.hpp"

#include <vector>

namespace engine {
    Grid::Grid(const Parameters& params) {
        mesh_ = Mesh::Create(CreateGeometry(params), FlatMaterial::Create(params.color));
        mesh_->GetMaterial()->fog = false;
        mesh_->GetGeometry()->SetName("grid");
        Add(mesh_);
    }

    auto Grid::CreateGeometry(const Parameters& params) const -> std::shared_ptr<Geometry> {
        std::vector<float> vertices;
        auto half_dimensions = static_cast<float>(params.dimensions / 2) * params.scale;
        if (params.dimensions & 1) {
            half_dimensions += params.scale / 2;
        }

        auto x_offset = -half_dimensions;
        for (auto i = 0; i <= params.dimensions; ++i) {
            vertices.emplace_back(x_offset);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(-half_dimensions);
            vertices.emplace_back(x_offset);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(half_dimensions);
            x_offset += params.scale;
        }

        auto z_offset = -half_dimensions;
        for (auto i = 0; i <= params.dimensions; ++i) {
            vertices.emplace_back(-half_dimensions);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(z_offset);
            vertices.emplace_back(half_dimensions);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(z_offset);
            z_offset += params.scale;
        }

        auto geometry = Geometry::Create(vertices, {});
        geometry->primitive = GeometryPrimitiveType::Lines;
        geometry->SetAttribute({
            .type = GeometryAttributeType::Position,
            .item_size = 3
        });

        return geometry;
    }
}