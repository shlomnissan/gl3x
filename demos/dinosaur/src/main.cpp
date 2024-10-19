// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/renderer.hpp>
#include <engine/core/window.hpp>
#include <engine/scene/camera_orthographic.hpp>
#include <engine/scene/scene.hpp>

using namespace engine;

auto main() -> int {
    auto window = Window {{
        .width = 600,
        .height = 150,
        .title = "Dinosaur Runner!"
    }};

    if (window.HasErrors()) return EXIT_FAILURE;

    auto renderer = Renderer({
        .width = window.Width(),
        .height = window.Height(),
        .clear_color = 0xF7F7F7
    });

    auto scene = Scene::Create();
    auto camera = CameraOrthographic::Create(
        0.0f, static_cast<float>(window.Width()),
        0.0f, static_cast<float>(window.Height())
    );

    window.Start([&renderer, &scene, &camera](const double){
        renderer.Render(scene.get(), camera.get());
    });

    return EXIT_SUCCESS;
}