// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

class ExampleSpotLight : public engine::Scene {
public:
    explicit ExampleSpotLight(std::shared_ptr<engine::Camera>);

private:
    std::shared_ptr<engine::Mesh> mesh_;
};