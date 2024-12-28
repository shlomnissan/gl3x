// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "example_phong_material.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExamplePhongMaterial::ExamplePhongMaterial(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 3.0f);
    Add(camera_controls);

    auto geometry = BoxGeometry::Create();
    auto material = PhongMaterial::Create();
    material->color = 0x049EF4;
    material->cull_backfaces = false;
    mesh_ = Mesh::Create(geometry, material);
    Add(mesh_);

    auto ambient_light = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient_light);

    auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({2.0f, 2.0f, 2.0f});
    Add(point_light);
}

auto ExamplePhongMaterial::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
    mesh_->transform.Rotate(Vector3::Right(), 1.0f * delta);
}