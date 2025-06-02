/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/nodes.hpp>
#include <gleam/resources.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleGridResource : public ExampleScene {
public:
    explicit ExampleGridResource(std::shared_ptr<gleam::Camera>);

    auto ContextMenu() -> void override;

private:
    gleam::Grid::Parameters grid_params_;

    std::shared_ptr<gleam::Grid> grid_;
};