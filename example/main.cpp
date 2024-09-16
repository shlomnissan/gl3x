// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>
#include <engine/core/renderer.hpp>
#include <engine/geometry/box_geometry.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>
#include <engine/scene/scene.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto renderer = engine::Renderer({
        .width = window.Width(),
        .height = window.Height()
    });

    auto scene = engine::Scene::Create();
    auto camera = engine::CameraPerspective::Create(60.0f, window.AspectRatio());
    camera->TranslateZ(2.0f);

    auto box = engine::BoxGeometry::Create({});
    auto mesh1 = engine::Mesh::Create(box);
    auto mesh2 = engine::Mesh::Create(box);
    mesh2->TranslateZ(-2.0f);

    scene->Add(mesh1);
    scene->Add(mesh2);

    window.Start([&](const double){
        mesh1->RotateY(0.01f);
        mesh2->RotateX(0.01f);

        renderer.Render(scene.get(), camera.get());
    });

    return 0;
}