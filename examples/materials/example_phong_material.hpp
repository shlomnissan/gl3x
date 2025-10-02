/*
===========================================================================
  GL3X https://gl3x.org
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
    std::shared_ptr<gleam::PhongMaterial> material_;
    std::shared_ptr<gleam::Mesh> mesh_;
    std::shared_ptr<gleam::Texture2D> texture_;
};