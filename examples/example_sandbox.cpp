// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/resources.hpp>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(
        camera, 5.0f,
        math::DegToRad(25.0f)
    );
    Add(camera_controls);

    Add(Grid::Create({
        .dimensions = 16,
        .scale = 0.25,
        .color = 0x333333
    }));

    auto sphere = Sphere {1.0f, 0.1f};
    Add(BoundingSphere::Create(sphere, 0x00FF00));
    Add(Arrow::Create(1.0f, 0.0f, 0x00FF00, 1.2f));
}

auto ExampleSandbox::Update(float delta) -> void {
    // Empty
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}