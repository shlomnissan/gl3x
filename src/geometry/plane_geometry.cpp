// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/geometry/plane_geometry.hpp"

#include <cassert>

namespace engine {

PlaneGeometry::PlaneGeometry(const Parameters& params) {
    assert(params.width > 0);
    assert(params.height > 0);
    assert(params.width_segments > 0);
    assert(params.height_segments > 0);

    GenerateGeometry(params);
    SetAttributes();
}

auto PlaneGeometry::GenerateGeometry(const Parameters& params) -> void {
    const auto width_half = params.width / 2;
    const auto height_half = params.height / 2;

    const auto grid_x = params.width_segments;
    const auto grid_y = params.height_segments;
    const auto grid_x1 = grid_x + 1;
    const auto grid_y1 = grid_y + 1;

    const auto segment_w = params.width / grid_x;
    const auto segment_h = params.height / grid_y;

    for (auto iy = 0; iy < grid_y1; ++iy) {
        const auto y = iy * segment_h - height_half;
        for (auto ix = 0; ix < grid_x1; ++ix) {
            const auto x = ix * segment_w - width_half;
            const auto u = static_cast<float>(ix) / grid_x;
            const auto v = 1 - (static_cast<float>(iy) / grid_y);

            vertex_data_.emplace_back(x);  // pos x
            vertex_data_.emplace_back(-y); // pos y
            vertex_data_.emplace_back(0);  // pos z
            vertex_data_.emplace_back(0);  // normal x
            vertex_data_.emplace_back(0);  // normal y
            vertex_data_.emplace_back(1);  // normal z
            vertex_data_.emplace_back(u);  // u
            vertex_data_.emplace_back(v);  // v
        }
    }

    for (auto iy = 0; iy < grid_y; ++iy) {
        for (auto ix = 0; ix < grid_x; ++ix) {
            const auto a = ix + grid_x1 * iy;
            const auto b = ix + grid_x1 * (iy + 1);
            const auto c = ix + 1 + grid_x1 * (iy + 1);
            const auto d = ix + 1 + grid_x1 * iy;

            index_data_.emplace_back(a);
            index_data_.emplace_back(b);
            index_data_.emplace_back(d);
            index_data_.emplace_back(b);
            index_data_.emplace_back(c);
            index_data_.emplace_back(d);
        }
    }
}

auto PlaneGeometry::SetAttributes() -> void {
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