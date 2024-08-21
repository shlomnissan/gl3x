// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <engine/core/timer.hpp>
#include <engine/core/window.hpp>
#include <engine/scene/scene.hpp>

#include <engine/temp/renderer.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto timer = engine::Timer {};
    auto renderer = engine::Renderer {window.width(), window.height()};

    auto scene = engine::Scene {};

    // TODO: create a parent node
    // TODO: create a child node
    // TODO: pass scene to renderer

    timer.Start();
    window.Start([&](const double _){
        renderer.render(scene);
    });

    return 0;
}