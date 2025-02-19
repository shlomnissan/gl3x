// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_sandbox.hpp"

#include <engine/resources.hpp>

#include <imgui.h>

using namespace engine;

ExampleSandbox::ExampleSandbox(std::shared_ptr<engine::Camera> camera) {
    const auto camera_controls = CameraOrbit::Create(camera, 5.0f);
    Add(camera_controls);

    const auto bounding_box = BoundingBox::Create({-1.0f, 1.0f}, 0xFF00C1);
    Add(bounding_box);
}

auto ExampleSandbox::ContextMenu() -> void {
    // Empty
}