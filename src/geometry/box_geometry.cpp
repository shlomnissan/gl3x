// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/geometry/box_geometry.hpp"

#include <cassert>

namespace engine {

BoxGeometry::BoxGeometry(const Parameters& params) {
    assert(params.width > 0);
    assert(params.height > 0);
    assert(params.depth > 0);
    assert(params.width_segments > 0);
    assert(params.height_segments > 0);
    assert(params.depth_segments > 0);

    BuildPlane({
        'z', 'y', 'x', -1, -1,
        params.depth, params.height, params.width,
        params.depth_segments, params.height_segments
    });

    BuildPlane({
        'z', 'y', 'x', 1, -1,
        params.depth, params.height, -params.width,
        params.depth_segments, params.height_segments
    });

    BuildPlane({
        'x', 'z', 'y', 1, 1,
        params.width, params.depth, params.height,
        params.width_segments, params.depth_segments
    });

    BuildPlane({
        'x', 'z', 'y', 1, -1,
        params.width, params.depth, -params.height,
        params.width_segments, params.depth_segments
    });

    BuildPlane({
        'x', 'y', 'z', 1, -1,
        params.width, params.height, params.depth,
        params.width_segments, params.height_segments
    });

    BuildPlane({
        'x', 'y', 'z', -1, -1,
        params.width, params.height, -params.depth,
        params.width_segments, params.height_segments
    });

    SetAttributes();
}

auto BoxGeometry::BuildPlane(const PlaneParams& params) -> void {
    const auto width_half = params.width / 2;
    const auto height_half = params.height / 2;
    const auto depth_half = params.depth / 2;

    const auto grid_x1 = params.grid_x + 1;
    const auto grid_y1 = params.grid_y + 1;

    const auto segment_w = params.width / params.grid_x;
    const auto segment_h = params.height / params.grid_y;

    const auto vec = Vector3 {};
    auto counter = 0;

    // TODO: implement
}

auto BoxGeometry::SetAttributes() -> void {
    SetAttribute({
        .type = GeometryAttributeType::kPosition,
        .item_size = 3,
        .offset = 0
    });

    SetAttribute({
        .type = GeometryAttributeType::kNormal,
        .item_size = 3,
        .offset = 3
    });

    SetAttribute({
        .type = GeometryAttributeType::kUV,
        .item_size = 2,
        .offset = 6
    });
}

}