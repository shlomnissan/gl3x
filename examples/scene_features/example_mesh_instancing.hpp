/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/core.hpp>
#include <gleam/nodes.hpp>

#include "example_scene.hpp"

#include <array>

class ExampleMeshInstancing : public ExampleScene {
public:
    ExampleMeshInstancing();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::array<std::shared_ptr<gleam::Mesh>, 2500> boxes_;
};