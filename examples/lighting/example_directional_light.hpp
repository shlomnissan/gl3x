/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <vglx/lights.hpp>
#include <vglx/materials.hpp>

class ExampleDirectionalLight : public ExampleScene {
public:
    ExampleDirectionalLight();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gl3x::DirectionalLight> directional_light_;
    std::shared_ptr<gl3x::PhongMaterial> phong_material_;
};