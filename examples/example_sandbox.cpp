// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 5.0f);
    Add(camera_controls);

    const auto geometry = BoxGeometry::Create();
    const auto material = PhongMaterial::Create();
    material->color = 0x049EF4;

    mesh_ = Mesh::Create(geometry, material);
    mesh_->SetScale({1.0f, 2.0f, 1.0f});
    Add(mesh_);

    auto sphere = geometry->BoundingSphere();
    sphere.ApplyTransform(mesh_->GetWorldTransform());
    Add(BoundingSphere::Create(sphere, 0xEEC584));

    auto ambient_light = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient_light);

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(point_light);
}

auto ExampleSandbox::Update(float delta) -> void {
    mesh_->RotateX(1.0f * delta);
    mesh_->RotateY(1.0f * delta);
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}