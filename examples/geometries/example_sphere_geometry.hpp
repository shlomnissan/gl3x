// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

class ExampleSphereGeometry : public engine::Scene {
public:
    explicit ExampleSphereGeometry(std::shared_ptr<engine::Camera>);

    auto Update(float delta) -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
    std::shared_ptr<engine::Mesh> wireframes_;
};