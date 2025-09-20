/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_debug_visuals.hpp"

#include "ui_helpers.hpp"

#include <array>

using namespace gleam;

ExampleDebugVisuals::ExampleDebugVisuals() {
    arrows_ = Node::Create();
    arrows_->Add(Arrow::Create({
        .direction = {0.5f, 0.0f, 0.0f},
        .origin = {0.0f, 0.0f, 0.0f},
        .color = 0xFF0000,
        .length = 1.2f
    }));

    arrows_->Add(Arrow::Create({
        .direction = {0.0f, 0.5f, 0.0f},
        .origin = {0.0f, 0.0f, 0.0f},
        .color = 0x00FF00,
        .length = 1.2f
    }));

    arrows_->Add(Arrow::Create({
        .direction = Cross(Vector3(0.5f, 0.0f, 0.0f), Vector3(0.0f, 0.5f, 0.0f)),
        .origin = {0.0f, 0.0f, 0.0f},
        .color = 0x0000FF,
        .length = 1.2f
    }));
    arrows_->TranslateY(0.1f);

    grid_ = Grid::Create(grid_params_);
}

auto ExampleDebugVisuals::OnAttached(SharedContextPointer context) -> void {
    Add(OrbitControls::Create(context->camera, {
        .radius = 5.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(45.0f)
    }));
}

auto ExampleDebugVisuals::OnUpdate(float _) -> void {
    if (curr_visual_ == "arrows" && !IsChild(arrows_.get())) {
        if (IsChild(grid_.get())) Remove(grid_);
        Add(arrows_);
    }

    if (curr_visual_ == "grid" && !IsChild(grid_.get())) {
        if (IsChild(arrows_.get())) Remove(arrows_);
        Add(grid_);
    }
}

auto ExampleDebugVisuals::ContextMenu() -> void {
    static bool dirty = false;
    static auto visuals = std::array<const char*, 2> {"arrows", "grid"};

    UIDropDown("visuals", visuals, curr_visual_,
        [this](std::string_view str) { curr_visual_ = str; }
    );

    if (curr_visual_ == "grid") {
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
}