// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_flat_material.hpp"

#include "ui_helpers.hpp"

#include <engine/geometries.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleFlatMaterial::ExampleFlatMaterial(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();
    material_ = FlatMaterial::Create();
    material_->color = 0x049EF4;
    mesh_ = Mesh::Create(geometry, material_);
    Add(mesh_);
}

auto ExampleFlatMaterial::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}

auto ExampleFlatMaterial::ContextMenu() -> void {
    static bool _ = false;

    UICheckbox("two_sided", material_->two_sided, _);
    UICheckbox("transparent", material_->transparent, _);
    UISliderFloat("opacity", material_->opacity, 0.0f, 1.0f, _);
}