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

auto DirectionalLight::Direction() const -> Vector3 {
    if (target != nullptr) {
        return Normalize(target->world_transform.Position() - world_transform.Position());
    }
    return Normalize(world_transform.Position());
}

auto DirectionalLight::UpdateDebugMesh() -> void {
    RemoveAllChildren();

    auto position = world_transform.Position();
    auto material = FlatMaterial::Create();
    material->color = color;

    auto target_pos = target != nullptr ? target->world_transform.Position() : Vector3::Zero();
    auto debugLine = Geometry::Create({
        position.x, position.y, position.z,
        target_pos.x, target_pos.y, target_pos.z
    });
    debugLine->primitive = GeometryPrimitiveType::Lines;
    debugLine->SetAttribute({GeometryAttributeType::Position, 3});

    // TODO: create debug plane

    auto mesh = Mesh::Create(debugLine, material);
    mesh->transformAutoUpdate = false;

    Add(mesh);
}

}