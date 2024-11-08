// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/lights/directional_light.hpp"

#include "engine/core/geometry.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/scene/mesh.hpp"

#include <vector>

namespace engine {

auto DirectionalLight::SetDebugMode(bool enabled) -> void {
    debug_mode = enabled;
    if (debug_mode && Children().empty()) {
        CreateDebugMesh();
    }
}

auto DirectionalLight::CreateDebugMesh() -> void {
    auto geometry = Geometry::Create({
        1.0f, 1.0f, 1.0f,
        target.x, target.y, target.z
    });
    geometry->primitive = GeometryPrimitiveType::Lines;
    geometry->SetAttribute({GeometryAttributeType::Position, 3});

    auto mesh = Mesh::Create(geometry, FlatMaterial::Create());
    mesh->transformAutoUpdate = false;
    Add(mesh);
}

}