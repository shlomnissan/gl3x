// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <engine/core.hpp>
#include <engine/math.hpp>
#include <engine/temp/renderer.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto timer = engine::Timer {};
    auto renderer = engine::Renderer {window.width(), window.height()};

    // TODO: create a scene
    // TODO: create a parent node
    // TODO: create a child node
    // TODO: pass scene to renderer

    timer.Start();
    window.Start([&](const double _){
        renderer.render();
    });

    return 0;
}