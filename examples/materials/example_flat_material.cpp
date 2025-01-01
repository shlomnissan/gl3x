// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_flat_material.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleFlatMaterial::ExampleFlatMaterial(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();
    auto material = FlatMaterial::Create();
    material->color = 0x049EF4;
    material->cull_backfaces = true;
    mesh_ = Mesh::Create(geometry, material);
    Add(mesh_);
}

auto ExampleFlatMaterial::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}