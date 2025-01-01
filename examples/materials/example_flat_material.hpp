// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

class ExampleFlatMaterial : public engine::Scene {
public:
    explicit ExampleFlatMaterial(std::shared_ptr<engine::Camera>);

    auto Update(float delta) -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
};