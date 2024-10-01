// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>
#include <engine/core/renderer.hpp>
#include <engine/geometry/box_geometry.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>
#include <engine/scene/scene.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Examples"}};
    auto renderer = engine::Renderer({
        .width = window.Width(),
        .height = window.Height()
    });

    auto scene = engine::Scene::Create();
    auto camera = engine::CameraPerspective::Create(60.0f, window.AspectRatio());
    camera->TranslateZ(2.0f);

    auto mesh1 = engine::Mesh::Create(
        engine::BoxGeometry::Create({})
    );

    scene->Add(mesh1);

    window.Start([&](const double){
        mesh1->RotateY(0.01f);
        mesh1->RotateX(0.01f);

        renderer.Render(scene.get(), camera.get());
    });

    return 0;
}