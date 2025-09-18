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

class ExampleFrustumCulling : public ExampleScene {
public:
    ExampleFrustumCulling();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

private:
    std::array<std::shared_ptr<gleam::Mesh>, 2500> boxes_;
};