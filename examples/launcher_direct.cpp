/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gleam/gleam.hpp>

#include "core/window.hpp"
#include "core/renderer.hpp"

#include <iostream>

using namespace gleam;

auto main() -> int {
    auto window = Window {{
        .title = "Examples",
        .width = 1024,
        .height = 768,
        .antialiasing = 0,
        .vsync = true
    }};
    auto init_window = window.Initialize();
    if (!init_window) {
        std::cerr << init_window.error() << '\n';
        return 1;
    }

    auto renderer = Renderer {{
        .framebuffer_width = window.FramebufferWidth(),
        .framebuffer_height = window.FramebufferHeight(),
        .clear_color = 0x000080
    }};
    auto init_renderer = renderer.Initialize();
    if (!init_renderer) {
        std::cerr << init_renderer.error() << '\n';
        return 1;
    }

    auto camera = PerspectiveCamera::Create({
        .fov = gleam::math::DegToRad(60.0f),
        .aspect = window.AspectRatio(),
        .near = 0.1f,
        .far = 1000.0f
    });

    auto context = SharedContext::Create(&window, camera.get());
    auto scene = Scene::Create();
    scene->SetContext(context.get());

    auto timer = FrameTimer {true}; // auto-start
    window.Start([&]() {
        const auto dt = timer.Tick();
        scene->Advance(dt);
        renderer.Render(scene.get(), camera.get());
    });

    return 0;
}