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

    auto geometry = Geometry::Create({
    //   px,    py,   pz,   nx,   ny,   nz,   r,    g,    b     a
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    });

    geometry->SetAttribute({VertexAttributeType::Position, 3});
    geometry->SetAttribute({VertexAttributeType::Normal, 3});
    geometry->SetAttribute({VertexAttributeType::Color, 4});

    auto material = UnlitMaterial::Create(0xFFFFFF);
    material->transparent = true;
    Add(Mesh::Create(geometry, material));
}

auto ExampleSandbox::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {.radius = 3.0f}));
}