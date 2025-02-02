// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>
#include <engine/materials.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleBlending : public ExampleScene {
public:
    explicit ExampleBlending(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;



private:
    struct SceneSettings {
        float opacity = 0.9f;
    };

    SceneSettings settings_;

    std::shared_ptr<engine::PhongMaterial> transparent_material_;
};