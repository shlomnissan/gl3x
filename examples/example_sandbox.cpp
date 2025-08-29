/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_sandbox.hpp"

#include <gleam/geometries.hpp>
#include <gleam/materials.hpp>
#include <gleam/nodes.hpp>
#include <gleam/math.hpp>

using namespace gleam;

namespace {

auto arrow = Arrow::Create({
    .direction = {1.0f, 0.0f, 0.0f},
    .origin = Vector3::Zero(),
    .color = 0x59CD90,
    .length = 1.0f
});

auto spherical = Spherical {1.0f, 0.0f, 0.0f};

}

ExampleSandbox::ExampleSandbox() {
    show_context_menu_ = false;

    const auto grid = Grid::Create({
        .size = 4.0f,
        .divisions = 16,
        .color = 0x333333
    });

    arrow->TranslateY(0.5f);
    arrow->SetDirection(spherical.ToVector3());

    Add(grid);
    Add(arrow);
}

auto ExampleSandbox::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(
        context->Parameters().camera, {
            .radius = 3.0f,
            .pitch = math::pi_over_4
        })
    );
}

auto ExampleSandbox::OnUpdate(float delta) -> void {
    spherical.phi += 1.0f * delta;
    arrow->SetDirection(spherical.ToVector3());
}