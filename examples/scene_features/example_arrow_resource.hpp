/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <memory>

#include "example_scene.hpp"

class ExampleArrowResource : public ExampleScene {
public:
    explicit ExampleArrowResource();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto ContextMenu() -> void override;
};