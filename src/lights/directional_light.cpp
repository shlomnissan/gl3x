// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/lights/directional_light.hpp"

#include "engine/core/geometry.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/scene/mesh.hpp"

#include <vector>

namespace engine {

auto DirectionalLight::Update(float delta) -> void {
    if (debug_mode) {
        UpdateDebugMesh();
    }
}

auto DirectionalLight::UpdateDebugMesh() -> void {
    RemoveAllChildren();

    auto position = GetWorldTransform()[3];
    auto material = FlatMaterial::Create();
    material->color = color;

    auto debugLine = Geometry::Create({
        position.x, position.y, position.z,
        0.0f, 0.0f, 0.0f // currently, the light always points to the origin
    });
    debugLine->primitive = GeometryPrimitiveType::Lines;
    debugLine->SetAttribute({GeometryAttributeType::Position, 3});

    // TODO: create debug plane

    auto mesh = Mesh::Create(debugLine, material);
    mesh->transformAutoUpdate = false;

    Add(mesh);
}

}