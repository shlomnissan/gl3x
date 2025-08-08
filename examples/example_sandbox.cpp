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
}

auto ExampleSandbox::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {.radius = 3.0f}));

    context->Loaders().Mesh->LoadAsync(
        "assets/plane.msh", [this](auto result) {
            if (result) {
                model_ = result.value();
                model_->RotateX(math::DegToRad(-90.0f));
                auto x = static_cast<Mesh*>(model_->Children().front().get());
                auto m = UnlitMaterial::Create(0xFFFFFF);
                x->SetMaterial(m);
                Add(model_);
            }
        }
    );
}