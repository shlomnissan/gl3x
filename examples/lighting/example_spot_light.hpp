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

class ExampleSpotLight : public ExampleScene {
public:
    ExampleSpotLight();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<vglx::PhongMaterial> phong_material_;
    std::shared_ptr<vglx::SpotLight> spot_light_;
};