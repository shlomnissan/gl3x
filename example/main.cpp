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
    auto parent_node = std::make_shared<engine::Node>();
    auto child_node = std::make_shared<engine::Node>();
    parent_node->Add(child_node);

    parent_node->Scale(0.5f);
    parent_node->Translate({-0.1f, 0.0f, 0.0f});
    child_node->Scale(0.2f);

    scene.Add(parent_node);

    timer.Start();
    window.Start([&](const double _){
        renderer.render(scene);
    });

    return 0;
}