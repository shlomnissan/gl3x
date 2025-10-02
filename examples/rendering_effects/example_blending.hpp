/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gl3x/materials.hpp>

#include <array>
#include <memory>

#include "example_scene.hpp"

class ExampleBlending : public ExampleScene {
public:
    ExampleBlending();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gl3x::PhongMaterial> transparent_material_;
};