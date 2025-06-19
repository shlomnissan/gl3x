/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/geometries.hpp>
#include <gleam/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleArbitraryMesh : public ExampleScene {
public:
    explicit ExampleArbitraryMesh(std::shared_ptr<gleam::Camera>);

    auto OnAttached() -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gleam::Node> mesh_;
};