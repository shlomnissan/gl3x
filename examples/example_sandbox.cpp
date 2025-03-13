// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
#include <engine/math.hpp>
#include <engine/resources.hpp>
#include <engine/resources/grid.hpp>

#include <cmath>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(
        camera, 5.0f,
        math::DegToRad(25.0f)
    );
    Add(camera_controls);

    Add(Grid::Create({
        .size = 10.0f,
        .divisions = 16,
        .color = 0x333333
    }));

    const auto color_red = Color {0xFF0000};

    const auto test_cam = CameraOrthographic::Create({.far = 1.0f});
    test_cam->UpdateViewTransform();

    const auto mat = test_cam->projection_transform * test_cam->view_transform;
    const auto frustum = Frustum {mat};

    const auto left = BoundingPlane::Create(frustum.planes[0], 2, 0xFF0000);
    Add(left);

    const auto right = BoundingPlane::Create(frustum.planes[1], 2, 0x00FF00);
    Add(right);
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}