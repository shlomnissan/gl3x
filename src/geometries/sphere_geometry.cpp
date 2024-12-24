// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/geometries/sphere_geometry.hpp"

#include <cassert>

namespace engine {

SphereGeometry::SphereGeometry(const Parameters& params) {
    assert(params.radius > 0.0f);
    assert(params.width_segments >= 3);
    assert(params.height_segments >= 2);
    assert(params.phi_start >= 0.0f);
    assert(params.phi_length >= 0.0f);
    assert(params.theta_start >= 0.0f);
    assert(params.theta_length >= 0.0f);

    GenerateGeometry(params);
    SetAttributes();
}

auto SphereGeometry::GenerateGeometry(const Parameters& params) -> void {
    // TODO: implement sphere geometry generation
}

auto SphereGeometry::SetAttributes() -> void {
    using enum GeometryAttributeType;

    SetAttribute({.type = Position, .item_size = 3});
    SetAttribute({.type = Normal, .item_size = 3});
    SetAttribute({.type = UV, .item_size = 2});
}

}