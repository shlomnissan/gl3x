// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "gleam/lights/point_light.hpp"

#include "gleam/geometries/sphere_geometry.hpp"

namespace gleam {

static constexpr auto debug_mesh_size = 0.2f;

auto PointLight::SetDebugMode(bool is_debug_mode) -> void {
    if (debug_mode_enabled != is_debug_mode) {
        if (is_debug_mode) {
            CreateDebugMesh();
        } else {
            Remove(debug_mesh_sphere_);
            debug_mesh_sphere_.reset();
        }
        debug_mode_enabled = is_debug_mode;
    }
}

auto PointLight::OnUpdate(float delta) -> void {
    if (debug_mode_enabled) {
        UpdateDebugMesh();
    }
}

auto PointLight::CreateDebugMesh() -> void {
    debug_mesh_material_ = FlatMaterial::Create();
    debug_mesh_material_->two_sided = true;
    debug_mesh_material_->color = color;
    debug_mesh_material_->wireframe = true;
    debug_mesh_material_->fog = false;
    debug_mesh_sphere_ = Mesh::Create(SphereGeometry::Create({
        .radius = 1,
        .width_segments = 4,
        .height_segments = 2
    }), debug_mesh_material_);
    debug_mesh_sphere_->geometry->SetName("point light sphere");

    Add(debug_mesh_sphere_);
    UpdateDebugMesh();
}

auto PointLight::UpdateDebugMesh() -> void {
    debug_mesh_sphere_->SetScale(debug_mesh_size);
    debug_mesh_material_->color = color;
}

}