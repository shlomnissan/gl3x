// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <engine/core/window.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/node.hpp>
#include <engine/scene/scene.hpp>

#include <engine/temp/renderer.hpp>

#include <memory>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto renderer = engine::Renderer {window.Width(), window.Height()};
    // TODO: engine::Radians(60.0f)
    auto camera = engine::CameraPerspective {45.0f, window.AspectRatio()};

    auto scene = engine::Scene {};
    auto node = std::make_shared<engine::Node>();
    node->Scale(0.5f);
    scene.Add(node);

    auto child = std::make_shared<engine::Node>();
    child->Scale(0.6f);
    child->TranslateX(0.5f);
    node->Add(child);

    window.Start([&](const double _){
        node->RotateX(0.01f);
        node->RotateY(0.01f);
        renderer.render(scene, &camera);
    });

    return 0;
}