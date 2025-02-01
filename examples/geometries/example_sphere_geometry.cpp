// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sphere_geometry.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

#include <imgui.h>

using namespace engine;

ExampleSphereGeometry::ExampleSphereGeometry(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto ambient = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient);

    auto directional_light = DirectionalLight::Create(0xFFFFFF, 1.0f);
    directional_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(directional_light);

    auto geometry = SphereGeometry::Create();

    auto base_material = PhongMaterial::Create();
    base_material->color = 0x049EF4;
    base_material->polygon_offset = {1.0f, 1.0f};
    mesh_ = Mesh::Create(geometry, base_material);
    Add(mesh_);

    auto wireframe_material = FlatMaterial::Create();
    wireframe_material->wireframe = true;
    wireframe_material->fog = false;
    wireframes_ = Mesh::Create(geometry, wireframe_material);
    mesh_->Add(wireframes_);
}

auto ExampleSphereGeometry::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 0.5f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 0.5f * delta);
}

auto ExampleSphereGeometry::ContextMenu() -> void {
    ImGui::Text("Sphere Geometry");
}