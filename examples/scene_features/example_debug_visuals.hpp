/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gl3x/nodes.hpp>

#include <memory>
#include <string>

#include "example_scene.hpp"

class ExampleDebugVisuals : public ExampleScene {
public:
    ExampleDebugVisuals();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::string curr_visual_ {"arrows"};

    gl3x::Grid::Parameters grid_params_ {
        .size = 4.0f,
        .divisions = 16,
        .color = gl3x::Color(0x333333)
    };

    std::shared_ptr<gl3x::Node> arrows_;
    std::shared_ptr<gl3x::Grid> grid_;
};