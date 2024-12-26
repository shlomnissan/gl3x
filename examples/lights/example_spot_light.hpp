// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <engine/nodes.hpp>

#include <memory>

class ExampleSpotLight : public engine::Scene {
public:
    explicit ExampleSpotLight(std::shared_ptr<engine::Camera>);

private:
    std::shared_ptr<engine::Mesh> mesh_;
};