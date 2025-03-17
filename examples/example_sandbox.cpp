// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/geometries.hpp>
#include <engine/lights.hpp>
#include <engine/materials.hpp>
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
        .size = 10.0f,
        .divisions = 16,
        .color = 0x333333
    }));

    const auto color_red = Color {0xFF0000};

    const auto test_cam = CameraOrthographic::Create({.far = 1.0f});
    test_cam->UpdateViewTransform();
    frustum_.SetWithViewProjection(
        test_cam->projection_transform *
        test_cam->view_transform
    );

    const auto left = BoundingPlane::Create(frustum_.planes[0], 2, 0xFF0000);
    Add(left);

    const auto right = BoundingPlane::Create(frustum_.planes[1], 2, 0x00FF00);
    Add(right);

    const auto bottom = BoundingPlane::Create(frustum_.planes[2], 2, 0x0000FF);
    Add(bottom);

    const auto top = BoundingPlane::Create(frustum_.planes[3], 2, 0xFFFF00);
    Add(top);

    const auto near = BoundingPlane::Create(frustum_.planes[4], 2, 0xFF00FF);
    Add(near);

    const auto far = BoundingPlane::Create(frustum_.planes[5], 2, 0x00FFFF);
    Add(far);

    sphere_ = BoundingSphere::Create({Vector3::Zero(), 0.3f}, 0xFCA001);
    Add(sphere_);
}

auto ExampleSandbox::Update(float delta) -> void {
    if (moving_left_) sphere_->TranslateX(-1.0f * delta);
    if (moving_right_) sphere_->TranslateX(1.0f * delta);
}

auto ExampleSandbox::OnKeyboardEvent(engine::KeyboardEvent* event) -> void {
    using enum engine::KeyboardEvent::Type;
    using enum engine::Key;

    if (event->type == Pressed) {
        if (event->key == Left) moving_left_ = true;
        if (event->key == Right) moving_right_ = true;
    }

    if (event->type == Released) {
        if (event->key == Left) moving_left_ = false;
        if (event->key == Right) moving_right_ = false;
    }
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}