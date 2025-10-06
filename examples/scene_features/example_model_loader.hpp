/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vglx/cameras.hpp>
#include <vglx/geometries.hpp>
#include <vglx/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleModelLoader : public ExampleScene {
public:
    ExampleModelLoader();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

private:
    std::shared_ptr<gl3x::Mesh> sphere_;
    std::shared_ptr<gl3x::Node> model_;
    std::shared_ptr<gl3x::Texture2D> alpha_map_;

    bool is_alpha_set {false};
};