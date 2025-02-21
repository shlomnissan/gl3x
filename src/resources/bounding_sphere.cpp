// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/resources/bounding_sphere.hpp"

#include "engine/materials/flat_material.hpp"
#include "engine/geometries/sphere_geometry.hpp"

namespace engine {

BoundingSphere::BoundingSphere(const Sphere& sphere, const Color& color) {
    auto material = FlatMaterial::Create(color);
    material->transparent = true;
    material->opacity = 0.5f;
    Add(Mesh::Create(CreateGeometry(sphere), material));
}

auto BoundingSphere::CreateGeometry(const Sphere& sphere) const -> std::shared_ptr<Geometry> {
    return SphereGeometry::Create({sphere.Radius()});
}

}