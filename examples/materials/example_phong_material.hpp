// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExamplePhongMaterial : public ExampleScene {
public:
    explicit ExamplePhongMaterial(std::shared_ptr<engine::Camera> camera);

    auto Update(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
};