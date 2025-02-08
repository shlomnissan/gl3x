// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>
#include <engine/materials.hpp>

#include <array>
#include <memory>

#include "example_scene.hpp"

class ExampleBlending : public ExampleScene {
public:
    explicit ExampleBlending(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::PhongMaterial> transparent_material_;

    std::array<const char*, 5> blending_modes_ {
        "none", "normal", "additive", "subtractive", "multiply"
    };
};