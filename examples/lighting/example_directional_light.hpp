/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <gl3x/lights.hpp>
#include <gl3x/materials.hpp>

class ExampleDirectionalLight : public ExampleScene {
public:
    ExampleDirectionalLight();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gl3x::DirectionalLight> directional_light_;
    std::shared_ptr<gl3x::PhongMaterial> phong_material_;
};