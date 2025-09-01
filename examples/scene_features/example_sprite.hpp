/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "example_scene.hpp"

#include "gleam/nodes/sprite.hpp"

#include <memory>

class ExampleSprite : public ExampleScene {
public:
    ExampleSprite();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto OnUpdate(float delta) -> void override;

private:
    std::shared_ptr<gleam::Sprite> sprite_;
};