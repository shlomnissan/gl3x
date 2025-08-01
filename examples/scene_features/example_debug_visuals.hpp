/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/nodes.hpp>

#include <memory>
#include <string>

#include "example_scene.hpp"

class ExampleDebugVisuals : public ExampleScene {
public:
    ExampleDebugVisuals();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::string curr_visual_ {"arrows"};

    gleam::Grid::Parameters grid_params_ {
        .size = 4.0f,
        .divisions = 16,
        .color = gleam::Color(0x333333)
    };

    std::shared_ptr<gleam::Node> arrows_;
    std::shared_ptr<gleam::Grid> grid_;
};