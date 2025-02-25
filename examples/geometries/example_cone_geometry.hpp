// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/geometries.hpp>
#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleConeGeometry : public ExampleScene {
public:
    explicit ExampleConeGeometry(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    engine::ConeGeometry::Parameters params_;

    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::Mesh> wireframes_;
};