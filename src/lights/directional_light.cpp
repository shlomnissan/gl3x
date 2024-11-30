// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/lights/directional_light.hpp"

#include "engine/core/geometry.hpp"
#include "engine/geometry/plane_geometry.hpp"
#include "engine/materials/flat_material.hpp"
#include "engine/scene/mesh.hpp"

#include <vector>

namespace engine {

auto DirectionalLight::Update(float delta) -> void {
    if (debug_mode) {
        UpdateDebugMesh();
    }
}

auto DirectionalLight::Direction() -> Vector3 {
    if (target != nullptr) {
        return Normalize(target->GetWorldPosition() - GetWorldPosition());
    }
    return Normalize(GetWorldPosition());
}

auto DirectionalLight::UpdateDebugMesh() -> void {
    RemoveAllChildren();

    auto position = GetWorldPosition();
    auto material = FlatMaterial::Create();
    material->cull_backfaces = false;
    material->color = color;
    material->wireframe = true;

    auto target_pos = target != nullptr ? target->GetWorldPosition() : Vector3::Zero();
    auto debugLine = Geometry::Create({
        position.x, position.y, position.z,
        target_pos.x, target_pos.y, target_pos.z
    });
    debugLine->primitive = GeometryPrimitiveType::Lines;
    debugLine->SetAttribute({GeometryAttributeType::Position, 3});

    auto debugPlane = PlaneGeometry::Create({});

    auto mesh_plane = Mesh::Create(debugPlane, material);
    auto mesh_line = Mesh::Create(debugLine, material);

    Add(mesh_plane);
    Add(mesh_line);

    mesh_plane->LookAt(target_pos);
    mesh_line->transformAutoUpdate = false;
}

}