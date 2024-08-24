// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <engine/core/timer.hpp>
#include <engine/core/window.hpp>
#include <engine/scene/scene.hpp>
#include <engine/scene/node.hpp>

#include <engine/temp/renderer.hpp>

#include <memory>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto timer = engine::Timer {};
    auto renderer = engine::Renderer {window.width(), window.height()};

    auto scene = engine::Scene {};
    auto node = std::make_shared<engine::Node>();
    node->Scale(0.5f);
    scene.Add(node);

    auto child = std::make_shared<engine::Node>();
    child->Scale(0.6f);
    child->TranslateX(0.5f);
    node->Add(child);

    timer.Start();
    window.Start([&](const double _){
        node->RotateY(static_cast<float>(timer.GetElapsedSeconds()));
        renderer.render(scene);
    });

    return 0;
}