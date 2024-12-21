// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "example_lights_spot.hpp"

#include <engine/lights.hpp>
#include <engine/resources.hpp>
#include <engine/geometries.hpp>
#include <engine/materials.hpp>
#include <engine/math.hpp>

using namespace engine;

ExampleLightsSpot::ExampleLightsSpot(std::shared_ptr<engine::Camera> camera) {
    const auto orientation = Euler({
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(45.0f),
    });
    const auto camera_controls = CameraOrbit::Create(camera, orientation);
    camera_controls->distance = 4.0f;
    Add(camera_controls);

    const auto grid = Grid::Create({
        .dimensions = 16,
        .scale = 0.25f,
        .color = 0x333333
    });
    Add(grid);

    const auto ambient_light = AmbientLight::Create(0xFFFFFF, 0.3f);
    Add(ambient_light);

    const auto spot_light = SpotLight::Create(0xFFFFFF, 1.0f);
    spot_light->transform.Translate({2.0f, 2.0f, -1.0f});
    spot_light->SetDebugMode(true);
    Add(spot_light);

    auto geometry = PlaneGeometry::Create({3, 3});
    auto material = PhongMaterial::Create();
    material->color = 0x049EF4;
    material->cull_backfaces = true;
    mesh_ = Mesh::Create(geometry, material);
    mesh_->transform.Rotate(Vector3::Right(), math::DegToRad(-90.0f));
    Add(mesh_);
}

auto ExampleLightsSpot::Update(float delta) -> void {
    // TODO: implement.
}