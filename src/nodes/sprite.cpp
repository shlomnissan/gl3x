/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "gl3x/nodes/sprite.hpp"

namespace gleam {

Sprite::Sprite(std::shared_ptr<SpriteMaterial> material)
  : geometry_(SharedGeometry()), material_(material) {
    if (material_ == nullptr) {
        material_ = SpriteMaterial::Create(0xFFFFFF);
    }
}

auto Sprite::SharedGeometry() -> std::shared_ptr<Geometry>& {
    static auto geometry = []() {
        auto g = Geometry::Create({
           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        }, {0, 1, 2, 0, 2, 3});

        g->SetAttribute({VertexAttributeType::Position, 3});
        g->SetAttribute({VertexAttributeType::UV, 2});

        return g;
    }();

    return geometry;
}

}