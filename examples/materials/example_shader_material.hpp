/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gleam/core.hpp>
#include <gleam/materials.hpp>
#include <gleam/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleShaderMaterial : public ExampleScene {
public:
    explicit ExampleShaderMaterial(std::shared_ptr<gleam::Camera>);

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    gleam::Timer timer_ {true};

    std::shared_ptr<gleam::ShaderMaterial> material_;
    std::shared_ptr<gleam::Mesh> mesh_;
};