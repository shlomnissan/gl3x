// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/geometries.hpp>
#include <engine/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExamplePlaneGeometry : public ExampleScene {
public:
    explicit ExamplePlaneGeometry(std::shared_ptr<engine::Camera>);

    auto Update(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    engine::PlaneGeometry::Parameters params_;

    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::Mesh> wireframes_;

    bool update_geometry_ {false};
};