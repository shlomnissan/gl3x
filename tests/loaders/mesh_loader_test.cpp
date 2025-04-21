// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/loaders/mesh_loader.hpp>

const auto mesh_loader = engine::MeshLoader::Create();

#pragma region Load Mesh Synchronously

TEST(MeshLoader, LoadMeshSynchronous) {
    mesh_loader->Load("assets/plane.obj", [](const auto& result) {
        EXPECT_TRUE(result);
    });
}

#pragma endregion