// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/materials.hpp>
#include <engine/math.hpp>
#include <engine/nodes.hpp>

#include "example_scene.hpp"

#include <array>

class ExampleLerpAnimationTest : public ExampleScene {
public:
    explicit ExampleLerpAnimationTest(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

    auto Update(float delta) -> void override;

private:
    std::shared_ptr<engine::Mesh> active_point_;
    std::shared_ptr<engine::PhongMaterial> active_material_;

    engine::Vector3 start_pos_ {-1.5f, 0.0f, 0.0f};
    engine::Vector3 end_pos_ {1.5f, 0.0f, 0.0f};
    engine::Vector3 start_scale_ {1.0f};
    engine::Vector3 end_scale_ {0.5f};
    engine::Color start_color_ {0xFE4A49};
    engine::Color end_color_ {0xFED766};

    float elapsed_time_ {0.0f};
};