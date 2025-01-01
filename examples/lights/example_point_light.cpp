// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_point_light.hpp"

#include <engine/materials.hpp>
#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/resources.hpp>
#include <engine/math.hpp>

using namespace engine;

ExamplePointLight::ExamplePointLight(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 5.0f);
    camera_controls->pitch = math::DegToRad(25.0f);
    camera_controls->yaw = math::DegToRad(45.0f);
    Add(camera_controls);

    const auto grid = Grid::Create({
        .dimensions = 16,
        .scale = 0.25f,
        .color = 0x333333
    });
    Add(grid);

    const auto ambient_light = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient_light);

    const auto point_light = PointLight::Create(0xFFFFFF, 1.0f);
    point_light->transform.Translate({1.0f, 2.0f, -2.0f});
    point_light->SetDebugMode(true);
    Add(point_light);

    auto geometry = BoxGeometry::Create();
    auto material = PhongMaterial::Create();
    material->color = 0x049EF4;
    material->cull_backfaces = true;
    mesh_ = Mesh::Create(geometry, material);
    mesh_->transform.Translate({0.0f, 0.5f, 0.0f});
    Add(mesh_);
}

auto ExamplePointLight::Update(float delta) -> void {
    mesh_->transform.Rotate(Vector3::Up(), 1.0f * delta);
}