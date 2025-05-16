// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_arrow_resource.hpp"

#include "ui_helpers.hpp"

#include <engine/resources.hpp>

using namespace engine;

ExampleArrowResource::ExampleArrowResource(std::shared_ptr<engine::Camera> camera) {
    show_context_menu_ = false;

    Add(OrbitControls::Create(camera, {
        .radius = 5.0f,
        .pitch = math::DegToRad(25.0f),
        .yaw = math::DegToRad(45.0f)
    }));

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

auto ExampleArrowResource::ContextMenu() -> void {
    // Empty
}