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
        if (debug_mesh_line_ == nullptr || debug_mesh_plane_ == nullptr) {
            CreateDebugMesh();
        }

        const auto target_world_pos = target != nullptr
            ? target->GetWorldPosition()
            : Vector3::Zero();


        debug_mesh_plane_->LookAt(target_world_pos);
        debug_mesh_line_->LookAt(target_world_pos);

        const auto length = (target_world_pos - GetWorldPosition()).Length();
        debug_mesh_line_->transform.Scale({1.0f, 1.0f, length});
    }
}

auto DirectionalLight::Direction() -> Vector3 {
    if (target != nullptr) {
        return Normalize(GetWorldPosition() - target->GetWorldPosition());
    }
    return Normalize(GetWorldPosition());
}

auto DirectionalLight::CreateDebugMesh() -> void {
    using enum GeometryAttributeType;
    using enum GeometryPrimitiveType;

    auto material = FlatMaterial::Create();
    material->cull_backfaces = false;
    material->color = color;
    material->wireframe = true;

    debug_mesh_line_ = Mesh::Create(Geometry::Create({
        0, 0, 0,
        0, 0, 1
    }), material);
    debug_mesh_line_->GetGeometry()->SetAttribute({Position, 3});
    debug_mesh_line_->GetGeometry()->primitive = Lines;
    debug_mesh_line_->transformAutoUpdate = false;
    Add(debug_mesh_line_);

    debug_mesh_plane_ = Mesh::Create(Geometry::Create({
        -1,  1, 0,
         1,  1, 0,
         1, -1, 0,
        -1, -1, 0
    }), material);
    debug_mesh_plane_->GetGeometry()->SetAttribute({Position, 3});
    debug_mesh_plane_->GetGeometry()->primitive = LineLoop;
    debug_mesh_plane_->transformAutoUpdate = false;
    Add(debug_mesh_plane_);
}

}