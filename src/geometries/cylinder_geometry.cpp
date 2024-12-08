// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/geometries/cylinder_geometry.hpp"

#include "engine/math/utilities.hpp"
#include "engine/math/vector3.hpp"

#include <cassert>
#include <cmath>

namespace engine {

CylinderGeometry::CylinderGeometry(const Paramaters& params) {
    assert(params.height > 0);
    assert(params.radial_segments > 0);
    assert(params.height_segments > 0);

    SetName("cylinder geometry");

    GenerateTorso(params);
    SetAttributes();
}

auto CylinderGeometry::GenerateTorso(const Paramaters& params) -> void {
    const auto half_height = params.height / 2;
    const auto slope = (params.radius_bottom - params.radius_top) / params.height;
    for (auto y = 0; y <= params.height_segments; ++y) {
        const auto v = static_cast<float>(y) / static_cast<float>(params.height_segments);
        const auto radius = params.radius_top + (params.radius_bottom - params.radius_top) * v;
        for (auto x = 0; x <= params.radial_segments; ++x) {
            const auto u = static_cast<float>(x) / static_cast<float>(params.radial_segments);
            const auto segment = u * math::two_pi;
            const auto sin_theta = std::sin(segment);
            const auto cos_theta = std::cos(segment);
            const auto normal = Vector3(sin_theta, slope, cos_theta).Normalize();

            vertex_data_.emplace_back(radius * sin_theta);                  // pos x
            vertex_data_.emplace_back(-v * params.height + half_height);    // pos y
            vertex_data_.emplace_back(radius * cos_theta);                  // pos z
            vertex_data_.emplace_back(normal.x);                            // normal x
            vertex_data_.emplace_back(normal.y);                            // normal y
            vertex_data_.emplace_back(normal.z);                            // normal z
            vertex_data_.emplace_back(u);                                   // u
            vertex_data_.emplace_back(1 - v);                               // v
        }
    }

    for (auto y = 0; y < params.height_segments; ++y) {
        for (auto x = 0; x < params.radial_segments; ++x) {
            const auto a = x + (params.radial_segments + 1) * y;
            const auto b = x + (params.radial_segments + 1) * (y + 1);
            const auto c = x + 1 + (params.radial_segments + 1) * (y + 1);
            const auto d = x + 1 + (params.radial_segments + 1) * y;

            index_data_.emplace_back(a);
            index_data_.emplace_back(b);
            index_data_.emplace_back(d);
            index_data_.emplace_back(b);
            index_data_.emplace_back(c);
            index_data_.emplace_back(d);
        }
    }
}

auto CylinderGeometry::GenerateCap(bool top) -> void {
    // TODO: impl.
}

auto CylinderGeometry::SetAttributes() -> void {
    SetAttribute({
        .type = GeometryAttributeType::Position,
        .item_size = 3
    });

    SetAttribute({
        .type = GeometryAttributeType::Normal,
        .item_size = 3
    });

    SetAttribute({
        .type = GeometryAttributeType::UV,
        .item_size = 2
    });
}

}