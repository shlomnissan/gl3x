// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "example_arrow_resource.hpp"

#include "ui_helpers.hpp"

#include <engine/resources.hpp>

using namespace engine;

ExampleArrowResource::ExampleArrowResource(std::shared_ptr<engine::Camera> camera) {
    show_context_menu_ = false;

    Add(CameraOrbit::Create(camera, 5.0f, math::DegToRad(25.0f), math::DegToRad(45.0f)));

    const auto arrows = Node::Create();
    Add(arrows);

    arrows->Add(Arrow::Create(
        Vector3(0.5f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Color(0xFF0000),
        1.2f
    ));

    arrows->Add(Arrow::Create(
        Vector3(0.0f, 0.5f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Color(0x00FF00),
        1.2f
    ));

    arrows->Add(Arrow::Create(
        Cross(Vector3(0.5f, 0.0f, 0.0f), Vector3(0.0f, 0.5f, 0.0f)),
        Vector3(0.0f, 0.0f, 0.0f),
        Color(0x0000FF),
        1.2f
    ));

    arrows->TranslateY(0.1f);
}

auto ExampleArrowResource::ContextMenu() -> void {
    // Empty
}