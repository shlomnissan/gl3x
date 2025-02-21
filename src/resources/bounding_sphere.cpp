// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/bounding_sphere.hpp"

#include "engine/math/utilities.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/geometries/sphere_geometry.hpp"

#include <cmath>

namespace engine {

BoundingSphere::BoundingSphere(const Sphere& sphere, const Color& color) {
    Add(Mesh::Create(CreateGeometry(sphere), FlatMaterial::Create(color)));
}

auto BoundingSphere::CreateGeometry(const Sphere& sphere) const -> std::shared_ptr<Geometry> {
    constexpr auto segments = 64.0f;

    std::vector<float> vertices;
    std::vector<unsigned> indices;

    for (auto i = 0; i <= static_cast<unsigned>(segments); ++i) {
        auto p = sphere.Center();
        auto theta = (static_cast<float>(i) / segments) * math::two_pi;
        p.x += sphere.Radius() * std::cos(theta);
        p.z += sphere.Radius() * std::sin(theta);

        vertices.emplace_back(p.x);
        vertices.emplace_back(p.y);
        vertices.emplace_back(p.z);

        if (i > 0) {
            indices.emplace_back(i - 1);
            indices.emplace_back(i);
        }
    }

    auto geometry = Geometry::Create(vertices, indices);
    geometry->primitive = GeometryPrimitiveType::Lines;
    geometry->SetAttribute({
        .type = GeometryAttributeType::Position,
        .item_size = 3
    });

    return geometry;
}

}