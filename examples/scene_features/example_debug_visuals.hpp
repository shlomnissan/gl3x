/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vglx/nodes.hpp>

#include <memory>
#include <string>

#include "example_scene.hpp"

class ExampleDebugVisuals : public ExampleScene {
public:
    ExampleDebugVisuals();

    auto OnAttached(vglx::SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::string curr_visual_ {"arrows"};

    vglx::Grid::Parameters grid_params_ {
        .size = 4.0f,
        .divisions = 16,
        .color = vglx::Color(0x333333)
    };

    std::shared_ptr<vglx::Node> arrows_;
    std::shared_ptr<vglx::Grid> grid_;
};