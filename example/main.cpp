// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/node.hpp>
#include <engine/scene/scene.hpp>

#include <engine/temp/renderer.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto renderer = engine::Renderer {window.Width(), window.Height()};
    auto camera = engine::CameraPerspective::Create(60.0f, window.AspectRatio());

    auto scene = engine::Scene::Create();
    auto node = engine::Node::Create();
    scene->Add(node);
    camera->TranslateZ(1.0f);

    window.Start([&](const double){
        node->RotateY(0.01f);
        renderer.render(scene.get(), camera.get());
    });

    return 0;
}