/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_sprite.hpp"
#include "gleam/nodes/orbit_controls.hpp"

using namespace gleam;

ExampleSprite::ExampleSprite() {
    show_context_menu_ = false;
}

auto ExampleSprite::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {.radius = 3.0f}));
}
