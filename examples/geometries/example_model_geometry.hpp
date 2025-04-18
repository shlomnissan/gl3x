// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleModelGeometry : public ExampleScene {
public:
    explicit ExampleModelGeometry(std::shared_ptr<engine::Camera>);

    auto OnAttached() -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::Mesh> wireframes_;
};