/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/core.hpp>
#include <gleam/materials.hpp>
#include <gleam/math.hpp>
#include <gleam/nodes.hpp>

#include "example_scene.hpp"

#include <array>

class ExampleLerpAnimationTest : public ExampleScene {
public:
    explicit ExampleLerpAnimationTest();

    auto OnAttached(gleam::SharedContext* context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<gleam::Mesh> active_point_;
    std::shared_ptr<gleam::PhongMaterial> active_material_;

    gleam::Vector3 start_pos_ {-1.5f, 0.0f, 0.0f};
    gleam::Vector3 end_pos_ {1.5f, 0.0f, 0.0f};
    gleam::Vector3 start_scale_ {1.0f};
    gleam::Vector3 end_scale_ {0.5f};
    gleam::Color start_color_ {0xFE4A49};
    gleam::Color end_color_ {0xFED766};

    float elapsed_time_ {0.0f};
};