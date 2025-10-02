/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gl3x/core.hpp>
#include <gl3x/nodes.hpp>

#include "example_scene.hpp"

class ExampleMeshInstancing : public ExampleScene {
public:
    ExampleMeshInstancing();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

private:
    std::shared_ptr<gl3x::InstancedMesh> boxes_ {};
};