/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <gl3x/lights.hpp>
#include <gl3x/materials.hpp>

class ExampleSpotLight : public ExampleScene {
public:
    ExampleSpotLight();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gl3x::PhongMaterial> phong_material_;
    std::shared_ptr<gl3x::SpotLight> spot_light_;
};