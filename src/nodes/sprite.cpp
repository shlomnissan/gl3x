/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gleam/nodes/sprite.hpp"

#include "gleam/materials/unlit_material.hpp"

namespace gleam {

namespace {

const auto geometry = []() {
    std::shared_ptr<Geometry> g =  Geometry::Create({
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    }, {0, 1, 2, 0, 2, 3});

    g->SetAttribute({VertexAttributeType::Position, 3});
    g->SetAttribute({VertexAttributeType::UV, 2});

    return g;
}();

}

Sprite::Sprite(std::shared_ptr<Material> material) : geometry_(geometry), material_(material) {
    if (material_ == nullptr) {
        material_ = UnlitMaterial::Create(0xFFFFFF);
    }
}

}