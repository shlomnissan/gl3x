// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/geometries.hpp>
#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleArbitraryMesh : public ExampleScene {
public:
    explicit ExampleArbitraryMesh(std::shared_ptr<engine::Camera>);

    auto OnAttached() -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<engine::Node> mesh_;
};