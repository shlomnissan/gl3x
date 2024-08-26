// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <engine/core/window.hpp>
#include <engine/math/utilities.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/node.hpp>
#include <engine/scene/scene.hpp>

#include <engine/temp/renderer.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto renderer = engine::Renderer {window.Width(), window.Height()};
    auto camera = engine::CameraPerspective::Create(
        engine::math::DegToRad(60.0f), window.AspectRatio()
    );

    auto scene = engine::Scene::Create();
    auto node = engine::Node::Create();
    node->Scale(0.5f);
    scene->Add(node);

    auto child = engine::Node::Create();
    child->Scale(0.6f);
    child->TranslateX(0.5f);
    node->Add(child);

    window.Start([&](const double _){
        node->RotateX(0.01f);
        node->RotateY(0.01f);
        renderer.render(scene.get(), camera.get());
    });

    return 0;
}