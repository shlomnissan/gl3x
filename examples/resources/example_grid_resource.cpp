// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_grid_resource.hpp"

#include "ui_helpers.hpp"

using namespace engine;

ExampleGridResource::ExampleGridResource(std::shared_ptr<engine::Camera> camera) {
    Add(CameraOrbit::Create(camera, {
        .radius = 5.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(45.0f)
    }));

    grid_params_ = {
        .size = 4.0f,
        .divisions = 16,
        .color = Color(0x333333)
    };

    grid_ = Grid::Create(grid_params_);

    Add(grid_);
}

auto ExampleGridResource::ContextMenu() -> void {
    static bool dirty = false;

    UIColor("color", &grid_params_.color[0], dirty, "color");
    UISliderFloat("size", grid_params_.size, 1.0, 10.0f, dirty);
    UISliderUnsigned("divisions", grid_params_.divisions, 1, 64, dirty);

    if (dirty) {
        dirty = false;
        auto grid = Grid::Create(grid_params_);
        auto grid_mesh = grid->Children().front();

        grid_->RemoveAllChildren();
        grid_->Add(grid_mesh);
    }
}