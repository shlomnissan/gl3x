/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/math.hpp>
#include <gleam/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleGridResource : public ExampleScene {
public:
    explicit ExampleGridResource();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto ContextMenu() -> void override;

private:
    gleam::Grid::Parameters grid_params_ {
        .size = 4.0f,
        .divisions = 16,
        .color = gleam::Color(0x333333)
    };

    std::shared_ptr<gleam::Grid> grid_;
};