/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "example_scene.hpp"

class ExampleSprite : public ExampleScene {
public:
    ExampleSprite();

    auto OnAttached(gleam::SharedContext* context) -> void override;
};