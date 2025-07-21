/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_debug_visuals.hpp"

#include "ui_helpers.hpp"

#include <gleam/core.hpp>

using namespace gleam;

ExampleDebugVisuals::ExampleDebugVisuals() {

}

auto ExampleDebugVisuals::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 3.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(-25.0f)
    }));
}

auto ExampleDebugVisuals::ContextMenu() -> void {

}