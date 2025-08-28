/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/lights/light.hpp"
#include "gleam/nodes/mesh.hpp"
#include "gleam/nodes/node.hpp"
#include "gleam/nodes/scene.hpp"

#include <memory>
#include <span>
#include <vector>

namespace gleam {

class RenderLists {
public:
    auto ProcessScene(Scene* scene) -> void;

    [[nodiscard]] auto Opaque() const -> std::span<Mesh* const> {
        return opaque_;
    }

    [[nodiscard]] auto Transparent() const -> std::span<Mesh* const> {
        return transparent_;
    }

    [[nodiscard]] auto Lights() const -> std::span<Light* const> {
        return lights_;
    }

private:
    std::vector<Mesh*> opaque_;

    std::vector<Mesh*> transparent_;

    std::vector<Light*> lights_;

    auto ProcessNode(Node*) -> void;

    auto Reset() -> void;
};

}