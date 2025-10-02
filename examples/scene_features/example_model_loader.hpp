/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gl3x/cameras.hpp>
#include <gl3x/geometries.hpp>
#include <gl3x/nodes.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleModelLoader : public ExampleScene {
public:
    ExampleModelLoader();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

private:
    std::shared_ptr<gleam::Mesh> sphere_;
    std::shared_ptr<gleam::Node> model_;
    std::shared_ptr<gleam::Texture2D> alpha_map_;

    bool is_alpha_set {false};
};