// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleBoxGeometry : public ExampleScene {
public:
    explicit ExampleBoxGeometry(std::shared_ptr<engine::Camera>);

    auto Update(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::Mesh> wireframes_;
};