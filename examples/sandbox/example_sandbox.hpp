/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <memory>

#include "example_scene.hpp"

class ExampleSandbox : public ExampleScene {
public:
    ExampleSandbox();

    auto OnAttached(SharedContextPointer context) -> void override;

private:
    std::shared_ptr<gleam::Node> model_;
};