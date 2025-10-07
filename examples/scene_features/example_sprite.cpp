/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_sprite.hpp"

#include "vglx/nodes/orbit_controls.hpp"

#include <print>

using namespace vglx;

ExampleSprite::ExampleSprite() {
    show_context_menu_ = false;

    Add(Grid::Create({
        .size = 4.0f,
        .divisions = 16,
        .color = 0x333333
    }));
}

auto ExampleSprite::OnAttached(SharedContextPointer context) -> void {
    Add(OrbitControls::Create(context->camera, {
        .radius = 3.0f,
        .pitch = math::pi_over_6
    }));

    context->texture_loader->LoadAsync(
        "assets/sprite.tex",
        [this](auto result) {
            if (result) {
                auto material = SpriteMaterial::Create();
                material->albedo_map = result.value();
                sprite_ = Sprite::Create(material);
                sprite_->SetScale(0.15f);
                sprite_->TranslateY(1.0f);
                Add(sprite_);
            } else {
                std::println(stderr, "{}", result.error());
            }
        }
    );
}

auto ExampleSprite::OnUpdate(float delta) -> void {
    if (sprite_) {
        sprite_->rotation += 1.0f * delta;
    }
}
