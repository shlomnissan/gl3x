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

auto DirectionalLight::Direction() const -> Vector3 {
    if (target != nullptr) {
        return Normalize(target->world_transform.GetPosition() - world_transform.GetPosition());
    }
    return Normalize(world_transform.GetPosition());
}

auto DirectionalLight::UpdateDebugMesh() -> void {
    RemoveAllChildren();

    auto position = world_transform.GetPosition();
    auto material = FlatMaterial::Create();
    material->color = color;
    material->wireframe = true;

    auto target_pos = target != nullptr ? target->world_transform.GetPosition() : Vector3::Zero();
    auto debugLine = Geometry::Create({
        position.x, position.y, position.z,
        target_pos.x, target_pos.y, target_pos.z
    });
    debugLine->primitive = GeometryPrimitiveType::Lines;
    debugLine->SetAttribute({GeometryAttributeType::Position, 3});

    auto debugPlane = PlaneGeometry::Create({});

    auto mesh_plane = Mesh::Create(debugPlane, material);
    auto mesh_line = Mesh::Create(debugLine, material);
    mesh_line->transformAutoUpdate = false;

    const auto forward = Normalize(position - target_pos);
    const auto right = Normalize(Cross(forward, Vector3::Up()));
    const auto up = Cross(right, forward);

    mesh_plane->transform = Transform {{
        {right.x, right.y, right.z, 0.0f},
        {up.x, up.y, up.z, 0.0f},
        {forward.x, forward.y, forward.z, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};

    Add(mesh_plane);
    Add(mesh_line);
}

}