// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/math.hpp>
#include <engine/resources.hpp>

#include <cmath>

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

    const auto color_red = Color {0xFF0000};

    sphere_ = BoundingSphere::Create({0.0f, 0.05f}, color_red);
    Add(sphere_);

    arrow_ = Arrow::Create(1.0f, 0.0f, color_red, 1.2f);
    Add(arrow_);

    const auto plane = Plane(Vector3::Up(), 1.0f);
    const auto bounding_plane = BoundingPlane::Create(plane, 1.0f, color_red);
    Add(bounding_plane);
}

auto ExampleSandbox::Update(float delta) -> void {
    auto time = static_cast<float>(timer_.GetElapsedSeconds());
    auto x_pos = std::sin(time) * 1.5f;
    auto y_pos = std::cos(time) * 1.5f;
    sphere_->transform.SetPosition({x_pos, 1.0f, y_pos});

    arrow_->SetDirection({x_pos, 1.0f, y_pos});
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}