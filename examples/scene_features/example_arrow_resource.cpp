/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "example_arrow_resource.hpp"

#include <gleam/nodes.hpp>

#include "ui_helpers.hpp"

using namespace gleam;

ExampleArrowResource::ExampleArrowResource() {
    show_context_menu_ = false;

    const auto arrows = Node::Create();
    Add(arrows);

    arrows->Add(Arrow::Create({
        .direction = {0.5f, 0.0f, 0.0f},
        .origin = {0.0f, 0.0f, 0.0f},
        .color = 0xFF0000,
        .length = 1.2f
    }));

    arrows->Add(Arrow::Create({
        .direction = {0.0f, 0.5f, 0.0f},
        .origin = {0.0f, 0.0f, 0.0f},
        .color = 0x00FF00,
        .length = 1.2f
    }));

    arrows->Add(Arrow::Create({
        .direction = Cross(Vector3(0.5f, 0.0f, 0.0f), Vector3(0.0f, 0.5f, 0.0f)),
        .origin = {0.0f, 0.0f, 0.0f},
        .color = 0x0000FF,
        .length = 1.2f
    }));

    arrows->TranslateY(0.1f);
}

auto ExampleArrowResource::OnAttached(gleam::SharedContext* context) -> void {
    Add(OrbitControls::Create(context->Parameters().camera, {
        .radius = 5.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(45.0f)
    }));
}

auto ExampleArrowResource::ContextMenu() -> void {
    // Empty
}