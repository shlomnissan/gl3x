// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_fog.hpp"

#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <imgui.h>

using namespace engine;

ExampleFog::ExampleFog(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();
    auto material = FlatMaterial::Create();
    material->color = 0x0F012FA;
    mesh_ = Mesh::Create(geometry, material);
    Add(mesh_);
}

auto ExampleFog::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}

auto ExampleFog::ContextMenu() -> void {
    ImGui::Text("Fog Effect");
}