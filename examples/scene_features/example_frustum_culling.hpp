/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/core.hpp>
#include <gleam/math.hpp>
#include <gleam/nodes.hpp>

#include "example_scene.hpp"

#include <array>

class ExampleFrustumCulling : public ExampleScene {
public:
    explicit ExampleFrustumCulling();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    gleam::Frustum frustum_;

    std::array<std::shared_ptr<gleam::Mesh>, 2500> boxes_;
};