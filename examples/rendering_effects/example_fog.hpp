/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <memory>

#include "example_scene.hpp"

class ExampleFog : public ExampleScene {
public:
    ExampleFog();

    auto OnAttached(const gleam::SharedContext* context) -> void override;

    auto ContextMenu() -> void override;
};