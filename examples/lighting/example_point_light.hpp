/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "example_scene.hpp"

#include <memory>

#include <gleam/lights.hpp>
#include <gleam/materials.hpp>

class ExamplePointLight : public ExampleScene {
public:
    ExamplePointLight();

    auto OnAttached(const gleam::SharedContext* context) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gleam::PhongMaterial> phong_material_;
    std::shared_ptr<gleam::PointLight> point_light_;
};