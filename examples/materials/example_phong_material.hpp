/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/materials.hpp>
#include <gleam/nodes.hpp>
#include <gleam/textures.hpp>

#include <memory>

#include "example_scene.hpp"

class ExamplePhongMaterial : public ExampleScene {
public:
    explicit ExamplePhongMaterial();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gleam::PhongMaterial> material_;
    std::shared_ptr<gleam::Mesh> mesh_;
    std::shared_ptr<gleam::Texture2D> texture_;
};