// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/geometries.hpp>
#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleCylinderGeometry : public ExampleScene {
public:
    explicit ExampleCylinderGeometry(std::shared_ptr<engine::Camera>);

    auto ContextMenu() -> void override;

private:
    engine::CylinderGeometry::Parameters params_;

    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::Mesh> wireframes_;
};