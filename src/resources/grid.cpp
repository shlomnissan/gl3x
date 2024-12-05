// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/resources/grid.hpp"

#include "engine/core/geometry.hpp"
#include "engine/materials.hpp"

#include <vector>

namespace engine {
    Grid::Grid(int dimensions) {
        mesh_ = Mesh::Create(CreateGeometry(dimensions), FlatMaterial::Create(0x404040));
        mesh_->GetGeometry()->SetName("grid");
        Add(mesh_);
    }

    auto Grid::CreateGeometry(int dimensions) const -> std::shared_ptr<Geometry> {
        std::vector<float> vertices;
        const auto scale = 0.25f;
        const auto half_dimensions = static_cast<float>(dimensions / 2) * scale;

        auto x_offset = -half_dimensions;
        for (auto i = 0; i <= dimensions; ++i) {
            vertices.emplace_back(x_offset);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(-half_dimensions);
            vertices.emplace_back(x_offset);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(half_dimensions);
            x_offset += scale;
        }

        auto z_offset = -half_dimensions;
        for (auto i = 0; i <= dimensions; ++i) {
            vertices.emplace_back(-half_dimensions);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(z_offset);
            vertices.emplace_back(half_dimensions);
            vertices.emplace_back(0.0f);
            vertices.emplace_back(z_offset);
            z_offset += scale;
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