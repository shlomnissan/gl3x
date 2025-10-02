/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gl3x/core.hpp>
#include <gl3x/materials.hpp>
#include <gl3x/nodes.hpp>
#include <gl3x/utilities.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleShaderMaterial : public ExampleScene {
public:
    ExampleShaderMaterial();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    gl3x::Timer timer_ {true};

    std::shared_ptr<gl3x::ShaderMaterial> material_;
    std::shared_ptr<gl3x::Mesh> mesh_;
};