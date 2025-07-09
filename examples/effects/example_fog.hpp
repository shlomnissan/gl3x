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
    explicit ExampleFog(std::shared_ptr<gleam::Camera>);

    auto ContextMenu() -> void override;
};