// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/lights/spot_light.hpp"

namespace engine {

auto SpotLight::SetDebugMode(bool is_debug_mode) -> void {
    if (debug_mode_enabled != is_debug_mode) {
        if (is_debug_mode) {
            CreateDebugMesh();
        } else {
            Remove(debug_mesh_cone_);
            debug_mesh_cone_.reset();
        }
        debug_mode_enabled = is_debug_mode;
    }
}

auto SpotLight::Update(float delta) -> void {
    if (debug_mode_enabled) {
        const auto target_world_pos = Vector3::Zero();

        debug_mesh_material_->color = color;
        debug_mesh_cone_->LookAt(target_world_pos);

        const auto length = (target_world_pos - GetWorldPosition()).Length();
        debug_mesh_cone_->transform.Scale({1.0f, 1.0f, length});
    }
}

auto SpotLight::CreateDebugMesh() -> void {
    using enum GeometryAttributeType;
    using enum GeometryPrimitiveType;

    debug_mesh_material_ = FlatMaterial::Create();
    debug_mesh_material_->cull_backfaces = false;
    debug_mesh_material_->color = color;
    debug_mesh_material_->wireframe = true;
    debug_mesh_material_->fog = false;

    debug_mesh_cone_ = Mesh::Create(Geometry::Create({
        0, 0, 0,
        0, 0, 1
    }), debug_mesh_material_);
    debug_mesh_cone_->GetGeometry()->SetName("directional light line");
    debug_mesh_cone_->GetGeometry()->SetAttribute({Position, 3});
    debug_mesh_cone_->GetGeometry()->primitive = Lines;
    debug_mesh_cone_->transformAutoUpdate = false;
    Add(debug_mesh_cone_);
}

}