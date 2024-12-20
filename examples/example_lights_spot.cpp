// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "example_lights_spot.hpp"

#include <engine/lights.hpp>
#include <engine/resources.hpp>
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
}

auto ExampleLightsSpot::Update(float delta) -> void {
    // TODO: implement.
}