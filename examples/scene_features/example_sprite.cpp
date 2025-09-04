/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_sprite.hpp"

#include "gleam/nodes/orbit_controls.hpp"
#include "gleam/nodes/sprite.hpp"

#include <print>
#include <memory>

using namespace gleam;

namespace {

std::shared_ptr<Sprite> sprite {nullptr};

}

ExampleSprite::ExampleSprite() {
    show_context_menu_ = false;

    Add(Grid::Create({
        .size = 4.0f,
        .divisions = 16,
        .color = 0x333333
    }));
}

auto ExampleSprite::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 3.0f,
        .pitch = math::pi_over_6
    }));

    context->Loaders().Texture->LoadAsync(
        "assets/sprite.tex",
        [this](auto result) {
            if (result) {
                auto material = SpriteMaterial::Create();
                material->albedo_map = result.value();
                sprite = Sprite::Create(material);
                sprite->SetScale(0.15f);
                sprite->TranslateY(1.0f);
                Add(sprite);
            } else {
                std::println(stderr, "{}", result.error());
            }
        }
    );
}

auto ExampleSprite::OnUpdate(float delta) -> void {
    if (sprite) {
        sprite->rotation += 1.0f * delta;
    }
}
