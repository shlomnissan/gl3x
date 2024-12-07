// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/lights/point_light.hpp"

#include "engine/geometries/box_geometry.hpp"

namespace engine {

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

auto PointLight::Update(float delta) -> void {
    debug_mesh_sphere_->world_transform = world_transform;
    debug_mesh_sphere_->world_transform.Scale(debug_mesh_size);
}

auto PointLight::CreateDebugMesh() -> void {
    debug_mesh_material_ = FlatMaterial::Create();
    debug_mesh_material_->cull_backfaces = false;
    debug_mesh_material_->color = color;
    debug_mesh_material_->wireframe = true;

    debug_mesh_sphere_ = Mesh::Create(BoxGeometry::Create({}), debug_mesh_material_);
    debug_mesh_sphere_->GetGeometry()->SetName("point light sphere");
    debug_mesh_sphere_->transformAutoUpdate = false;
    Add(debug_mesh_sphere_);
}

}