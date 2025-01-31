// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include <engine/core.hpp>
#include <engine/materials.hpp>
#include <engine/nodes.hpp>

#include <memory>

class ExampleShaderMaterial : public engine::Scene {
public:
    explicit ExampleShaderMaterial(std::shared_ptr<engine::Camera>);

    auto Update(float delta) -> void override;

private:
    engine::Timer timer_ {true};

    std::shared_ptr<engine::ShaderMaterial> material_;
    std::shared_ptr<engine::Mesh> mesh_;
};