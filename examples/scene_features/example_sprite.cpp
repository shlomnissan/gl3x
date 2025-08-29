/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_sprite.hpp"

#include "gleam/nodes/orbit_controls.hpp"
#include "gleam/nodes/sprite.hpp"

using namespace gleam;

ExampleSprite::ExampleSprite() {
    show_context_menu_ = false;

    Add(Grid::Create({
        .size = 4.0f,
        .divisions = 16,
        .color = 0x333333
    }));

    Add(Sprite::Create());
}

auto ExampleSprite::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 3.0f,
        .pitch = math::pi_over_6
    }));
}
