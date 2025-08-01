/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/materials.hpp>

#include <array>
#include <memory>

#include "example_scene.hpp"

class ExampleBlending : public ExampleScene {
public:
    ExampleBlending();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gleam::PhongMaterial> transparent_material_;
};