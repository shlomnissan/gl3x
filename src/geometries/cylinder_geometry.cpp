// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/geometries/cylinder_geometry.hpp"

#include <cassert>

namespace engine {

CylinderGeometry::CylinderGeometry(const Paramaters& params) {
    assert(params.radius_top > 0);
    assert(params.radius_bottom > 0);
    assert(params.height > 0);
    assert(params.radial_segments > 0);
    assert(params.height_segments > 0);

    SetName("cylinder geometry");
}

auto CylinderGeometry::GenerateTorso() -> void {
    // TODO: impl.
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