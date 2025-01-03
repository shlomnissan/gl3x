// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

class ExampleDirectionalLight : public engine::Scene {
public:
    explicit ExampleDirectionalLight(std::shared_ptr<engine::Camera>);
};