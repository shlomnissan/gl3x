// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/core/window.hpp>
#include <engine/core/renderer.hpp>
#include <engine/geometry/box_geometry.hpp>
#include <engine/materials/flat_material.hpp>
#include <engine/materials/phong_material.hpp>
#include <engine/scene/camera_perspective.hpp>
#include <engine/scene/mesh.hpp>
#include <engine/scene/scene.hpp>
#include <engine/textures/texture_2d.hpp>

auto main() -> int {
    auto window = engine::Window {{.title = "Examples"}};
    auto renderer = engine::Renderer({
        .width = window.Width(),
        .height = window.Height(),
        .clear_color = {0.0f, 0.0f, 0.5f, 1.0f}
    });

    auto scene = engine::Scene::Create();
    auto camera = engine::CameraPerspective::Create(60.0f, window.AspectRatio());
    camera->TranslateZ(2.0f);

    auto mesh_flat = engine::Mesh::Create(
        engine::BoxGeometry::Create({}),
        engine::FlatMaterial::Create({})
    );
    mesh_flat->TranslateX(0.6f);
    mesh_flat->Scale(0.7f);


    auto mesh_shiny = engine::Mesh::Create(
        engine::BoxGeometry::Create({}),
        engine::PhongMaterial::Create({})
    );
    mesh_shiny->TranslateX(-0.6f);
    mesh_shiny->Scale(0.7f);

    scene->Add(mesh_flat);
    scene->Add(mesh_shiny);

    window.Start([&](const double){
        mesh_flat->RotateY(0.01f);
        mesh_shiny->RotateX(0.01f);

        renderer.Render(scene.get(), camera.get());
    });

    return 0;
}