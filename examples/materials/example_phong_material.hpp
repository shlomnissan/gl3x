/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gl3x/materials.hpp>
#include <gl3x/nodes.hpp>
#include <gl3x/textures.hpp>

#include <memory>

#include "example_scene.hpp"

class ExamplePhongMaterial : public ExampleScene {
public:
    ExamplePhongMaterial();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gl3x::PhongMaterial> material_;
    std::shared_ptr<gl3x::Mesh> mesh_;
    std::shared_ptr<gl3x::Texture2D> texture_;
};