// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_grid_resource.hpp"

#include "ui_helpers.hpp"

#include <engine/resources.hpp>

using namespace engine;

ExampleGridResource::ExampleGridResource(std::shared_ptr<engine::Camera> camera) {
    show_context_menu_ = false;

    Add(CameraOrbit::Create(camera, 5.0f, math::DegToRad(25.0f), math::DegToRad(45.0f)));
    Add(Grid::Create({.size = 4, .divisions = 16, .color = 0x333333}));
}

auto ExampleGridResource::ContextMenu() -> void {
    // Empty
}