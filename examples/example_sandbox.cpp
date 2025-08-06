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

using namespace gleam;

ExampleSandbox::ExampleSandbox() {
    show_context_menu_ = false;

    Add(Mesh::Create(
        PlaneGeometry::Create(),
        UnlitMaterial::Create(0xFF0000)
    ));
}

auto ExampleSandbox::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {.radius = 3.0f}));
}