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

namespace {

std::shared_ptr<Sprite> sprite;

}

ExampleSprite::ExampleSprite() {
    show_context_menu_ = false;

    Add(Grid::Create({
        .size = 4.0f,
        .divisions = 16,
        .color = 0x333333
    }));

    sprite = Sprite::Create();
    sprite->SetScale(0.3f);
    Add(sprite);
}

auto ExampleSprite::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 3.0f,
        .pitch = math::pi_over_6
    }));
}

auto ExampleSprite::OnUpdate(float delta) -> void {
    sprite->anchor = {0.0f, 0.0f};
    sprite->rotation += 1.0f * delta;
}
