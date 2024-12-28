// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/lights/point_light.hpp"

#include "engine/geometries/sphere_geometry.hpp"

#include "engine/math/transform.hpp"

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
    if (debug_mode_enabled) {
        // TODO: update this logic once the transform class is refactored.
        auto t = Transform {};
        t.Scale(debug_mesh_size);
        debug_mesh_sphere_->world_transform = world_transform * t.Get();
    }
}

auto PointLight::CreateDebugMesh() -> void {
    debug_mesh_material_ = FlatMaterial::Create();
    debug_mesh_material_->cull_backfaces = false;
    debug_mesh_material_->color = color;
    debug_mesh_material_->wireframe = true;
    debug_mesh_material_->fog = false;
    debug_mesh_sphere_ = Mesh::Create(SphereGeometry::Create({
        .radius = 1,
        .width_segments = 4,
        .height_segments = 2
    }), debug_mesh_material_);
    debug_mesh_sphere_->GetGeometry()->SetName("point light sphere");
    debug_mesh_sphere_->transformAutoUpdate = false;
    Add(debug_mesh_sphere_);
}

}