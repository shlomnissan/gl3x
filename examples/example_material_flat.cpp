// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "example_material_flat.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleMaterialFlat::ExampleMaterialFlat(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera);
    camera_controls->distance = 3.0f;
    Add(camera_controls);

    auto geometry = BoxGeometry::Create({});
    auto material = FlatMaterial::Create();
    material->color = 0x049EF4;
    material->cull_backfaces = true;
    mesh_ = Mesh::Create(geometry, material);
    Add(mesh_);
}

auto ExampleMaterialFlat::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}