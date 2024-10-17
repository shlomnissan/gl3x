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

using namespace engine;

auto main() -> int {
    auto window = Window {{.title = "Examples"}};
    if (window.HasErrors()) {
        return EXIT_FAILURE;
    }

    auto renderer = Renderer({
        .width = window.Width(),
        .height = window.Height(),
        .clear_color = {0.0f, 0.0f, 0.5f, 1.0f}
    });

    auto scene = Scene::Create();
    auto camera = CameraPerspective::Create(60.0f, window.AspectRatio());
    camera->TranslateZ(2.0f);

    auto flat_material = FlatMaterial::Create();
    auto flat_mesh = Mesh::Create(BoxGeometry::Create({}), flat_material);

    flat_material->texture_map = Texture2D::Create("assets/checker.png");
    flat_mesh->TranslateX(0.6f);
    flat_mesh->Scale(0.7f);

    auto shiny_material = PhongMaterial::Create();
    auto shiny_mesh = Mesh::Create(BoxGeometry::Create({}), shiny_material);

    shiny_material->color = 0x47A8BD; // Moonstone
    shiny_mesh->TranslateX(-0.6f);
    shiny_mesh->Scale(0.7f);

    scene->Add(flat_mesh);
    scene->Add(shiny_mesh);

    window.Start([&](const double){
        flat_mesh->RotateY(0.01f);
        shiny_mesh->RotateX(0.01f);

        renderer.Render(scene.get(), camera.get());
    });

    return EXIT_SUCCESS;
}