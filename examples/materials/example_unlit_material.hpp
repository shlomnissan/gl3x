/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <vglx/materials.hpp>
#include <vglx/nodes.hpp>
#include <vglx/textures.hpp>

#include <memory>

#include "example_scene.hpp"

class ExampleUnlitMaterial : public ExampleScene {
public:
    ExampleUnlitMaterial();

    auto OnAttached(SharedContextPointer context) -> void override;

    auto OnUpdate(float delta) -> void override;

    auto ContextMenu() -> void override;

private:
    std::shared_ptr<vglx::UnlitMaterial> material_;
    std::shared_ptr<vglx::Mesh> mesh_;
    std::shared_ptr<vglx::Texture2D> texture_;
};