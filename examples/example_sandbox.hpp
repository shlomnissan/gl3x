// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/nodes.hpp>

#include <memory>

class ExampleSandbox : public engine::Scene {
public:
    explicit ExampleSandbox(std::shared_ptr<engine::Camera>);

    auto Update(float delta) -> void override;
};