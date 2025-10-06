/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vglx/core.hpp>
#include <vglx/materials.hpp>
#include <vglx/nodes.hpp>
#include <vglx/utilities.hpp>

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