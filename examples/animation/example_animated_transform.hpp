/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vglx/core.hpp>
#include <vglx/materials.hpp>
#include <vglx/math.hpp>
#include <vglx/nodes.hpp>

#include "example_scene.hpp"

#include <array>

class ExampleAnimatedTransform : public ExampleScene {
public:
    ExampleAnimatedTransform();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

private:
    std::shared_ptr<gl3x::Mesh> active_point_;
    std::shared_ptr<gl3x::PhongMaterial> active_material_;

    gl3x::Vector3 start_pos_ {-1.5f, 0.0f, 0.0f};
    gl3x::Vector3 end_pos_ {1.5f, 0.0f, 0.0f};
    gl3x::Vector3 start_scale_ {1.0f};
    gl3x::Vector3 end_scale_ {0.5f};
    gl3x::Color start_color_ {0xFE4A49};
    gl3x::Color end_color_ {0xFED766};

    float elapsed_time_ {0.0f};
};