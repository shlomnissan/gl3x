// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>
#include <engine/core/geometry/plane_geometry.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>
#include <engine/scene/scene.hpp>

#include <engine/temp/renderer.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Example"}};
    auto renderer = engine::Renderer {window.Width(), window.Height()};
    auto camera = engine::CameraPerspective::Create(60.0f, window.AspectRatio());
    auto scene = engine::Scene::Create();
    auto geometry = engine::PlaneGeometry::Create({
        .width = 1.0f,
        .height = 1.0f,
        .width_segments = 2,
        .height_segments = 2
    });

    auto mesh = engine::Mesh::Create(geometry);
    scene->Add(mesh);
    camera->TranslateZ(1.0f);

    window.Start([&](const double){
        mesh->RotateY(0.01f);
        renderer.render(scene.get(), camera.get());
    });

    return 0;
}