// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/geometries/sphere_geometry.hpp"

#include "engine/math/vector3.hpp"

#include <algorithm>
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
    const auto theta_end = std::min(params.theta_start + params.theta_length, math::pi);

    for (auto iy = 0; iy <= params.height_segments; ++iy) {
        const auto v = static_cast<float>(iy) / static_cast<float>(params.height_segments);
        for (auto ix = 0; ix <= params.width_segments; ++ix) {
            const auto u = static_cast<float>(ix) / static_cast<float>(params.width_segments);

            auto vec = Vector3 {};

            vec.x = -params.radius *
                std::cos(params.phi_start + u * params.phi_length) *
                std::sin(params.theta_start + v * params.theta_length);

            vec.y = params.radius *
                std::cos(params.theta_start + v * params.theta_length);

            vec.z = params.radius *
                std::sin(params.phi_start + u * params.phi_length) *
                std::sin(params.theta_start + v * params.theta_length);

            // set position
            vertex_data_.emplace_back(vec.x);  // pos x
            vertex_data_.emplace_back(vec.y);  // pos y
            vertex_data_.emplace_back(vec.z);  // pos z

            vec.Normalize();

            // set normals
            vertex_data_.emplace_back(vec.x);  // normal x
            vertex_data_.emplace_back(vec.y);  // normal y
            vertex_data_.emplace_back(vec.z);  // normal z

            // set uvs
            vertex_data_.insert(vertex_data_.end(), {u, 1 - v});
        }
    }

    for (auto iy = 0; iy < params.height_segments; ++iy) {
        for (auto ix = 0; ix < params.width_segments; ++ix) {
            const auto a = ix + (params.width_segments + 1) * iy;
            const auto b = ix + (params.width_segments + 1) * (iy + 1);
            const auto c = ix + 1 + (params.width_segments + 1) * (iy + 1);
            const auto d = ix + 1 + (params.width_segments + 1) * iy;

            if (iy != 0 || params.theta_start > 0) {
                index_data_.emplace_back(a);
                index_data_.emplace_back(b);
                index_data_.emplace_back(d);
            }

            if (iy != params.height_segments - 1 || theta_end < math::pi) {
                index_data_.emplace_back(b);
                index_data_.emplace_back(c);
                index_data_.emplace_back(d);
            }
        }
    }
}

auto SphereGeometry::SetAttributes() -> void {
    using enum GeometryAttributeType;

    SetAttribute({.type = Position, .item_size = 3});
    SetAttribute({.type = Normal, .item_size = 3});
    SetAttribute({.type = UV, .item_size = 2});
}

}