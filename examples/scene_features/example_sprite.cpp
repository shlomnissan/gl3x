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

    Add(Grid::Create({
        .size = 4.0f,
        .divisions = 16,
        .color = 0x333333
    }));

    sprite_ = Sprite::Create();
    sprite_->SetScale(0.3f);
    Add(sprite_);
}

auto ExampleSprite::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 3.0f,
        .pitch = math::pi_over_6
    }));
}

auto ExampleSprite::OnUpdate(float delta) -> void {
    sprite_->rotation += 1.0f * delta;
}
