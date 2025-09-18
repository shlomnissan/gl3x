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

class ExampleMeshInstancing : public ExampleScene {
public:
    ExampleMeshInstancing();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

private:
    std::shared_ptr<gleam::InstancedMesh> boxes_ {};
};