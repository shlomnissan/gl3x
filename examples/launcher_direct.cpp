/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gleam/gleam.hpp>

#include "examples.hpp"

#include <iostream>

using namespace gleam;

auto main() -> int {
    auto window = Window {{
        .title = "Examples (Direct Initialization)",
        .width = 1024,
        .height = 768,
        .antialiasing = 0,
        .vsync = false
    }};
    auto init_window = window.Initialize();
    if (!init_window) {
        std::cerr << init_window.error() << '\n';
        return 1;
    }

    auto renderer = Renderer {{
        .framebuffer_width = window.FramebufferWidth(),
        .framebuffer_height = window.FramebufferHeight(),
        .clear_color = 0x444444
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

    auto context = std::make_unique<SharedContext> (
        camera.get(),
        window.AspectRatio(),
        window.FramebufferWidth(),
        window.FramebufferHeight(),
        window.Width(),
        window.Height()
    );

    auto timer = FrameTimer {true}; // auto-start
    auto stats = Stats {};
    auto examples = Examples {[&context](std::shared_ptr<Scene> scene){
        scene->SetContext(context.get());
    }};

    while(!window.ShouldClose()) {
        window.PollEvents();

        const auto dt = timer.Tick();
        examples.scene->Advance(dt);

        window.BeginUIFrame();
        examples.Draw();
        stats.Draw();

        stats.BeforeRender();
        renderer.Render(examples.scene.get(), camera.get());
        window.EndUIFrame();

        stats.AfterRender(renderer.RenderedObjectsPerFrame());
        window.SwapBuffers();
    }

    return 0;
}