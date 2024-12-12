// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <engine/nodes.hpp>

#include <memory>

class ExampleMaterialsFlat : public engine::Scene {
public:
    explicit ExampleMaterialsFlat(std::shared_ptr<engine::Camera>);

    auto Update(float delta) -> void override;

private:
    std::shared_ptr<engine::Mesh> mesh_;
};