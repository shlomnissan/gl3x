// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/lights/directional_light.hpp"

namespace engine {

static constexpr auto debug_mesh_size = 0.5f;

auto DirectionalLight::Direction() -> Vector3 {
    if (target != nullptr) {
        return Normalize(GetWorldPosition() - target->GetWorldPosition());
    }
    return Normalize(GetWorldPosition());
}

auto DirectionalLight::SetDebugMode(bool is_debug_mode) -> void {
    if (debug_mode_enabled != is_debug_mode) {
        if (is_debug_mode) {
            CreateDebugMesh();
        } else {
            Remove(debug_mesh_line_);
            Remove(debug_mesh_plane_);
            debug_mesh_line_.reset();
            debug_mesh_plane_.reset();
        }
        debug_mode_enabled = is_debug_mode;
    }
}

auto DirectionalLight::OnUpdate(float delta) -> void {
    if (debug_mode_enabled) {
        UpdateDebugMesh();
    }
}

auto DirectionalLight::CreateDebugMesh() -> void {
    using enum GeometryAttributeType;
    using enum GeometryPrimitiveType;

    debug_mesh_material_ = FlatMaterial::Create();
    debug_mesh_material_->two_sided = true;
    debug_mesh_material_->color = color;
    debug_mesh_material_->wireframe = true;
    debug_mesh_material_->fog = false;

    debug_mesh_line_ = Mesh::Create(Geometry::Create({
        0, 0, 0,
        0, 0, 1
    }), debug_mesh_material_);
    debug_mesh_line_->geometry->SetName("directional light line");
    debug_mesh_line_->geometry->SetAttribute({Position, 3});
    debug_mesh_line_->geometry->primitive = Lines;
    debug_mesh_line_->transform_auto_update = false;
    Add(debug_mesh_line_);

    debug_mesh_plane_ = Mesh::Create(Geometry::Create({
        -1,  1, 0,
         1,  1, 0,
         1, -1, 0,
        -1, -1, 0
    }), debug_mesh_material_);
    debug_mesh_plane_->geometry->SetName("directional light plane");
    debug_mesh_plane_->geometry->SetAttribute({Position, 3});
    debug_mesh_plane_->geometry->primitive = LineLoop;
    debug_mesh_plane_->transform_auto_update = false;

    Add(debug_mesh_plane_);
    UpdateDebugMesh();
}

auto DirectionalLight::UpdateDebugMesh() -> void {
    const auto target_world_pos = target != nullptr
        ? target->GetWorldPosition()
        : Vector3::Zero();

    debug_mesh_plane_->LookAt(target_world_pos);
    debug_mesh_line_->LookAt(target_world_pos);
    debug_mesh_material_->color = color;

    const auto length = (target_world_pos - GetWorldPosition()).Length();
    debug_mesh_plane_->SetScale(debug_mesh_size);
    debug_mesh_line_->SetScale({1.0f, 1.0f, length});
}

}