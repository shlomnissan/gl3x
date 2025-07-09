/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_grid_resource.hpp"

#include "ui_helpers.hpp"

using namespace gleam;

ExampleGridResource::ExampleGridResource() {
    grid_ = Grid::Create({
        .size = 4.0f,
        .divisions = 16,
        .color = Color(0x333333)
    });

    Add(grid_);
}

auto ExampleGridResource::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 5.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(45.0f)
    }));
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