// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/core/geometry.hpp>
#include <engine/loaders/mesh_loader.hpp>
#include <engine/nodes/mesh.hpp>

#include <future>
#include <thread>

const auto mesh_loader = engine::MeshLoader::Create();

#pragma region Helpers

template <typename Callback>
auto RunAsyncTest(const std::string& file_path, Callback callback) {
    auto main_thread_id = std::this_thread::get_id();
    auto promise = std::promise<void> {};
    auto future = promise.get_future();

    mesh_loader->LoadAsync(file_path, [&](const auto& result) {
        callback(result, main_thread_id);
        promise.set_value();
    });

    auto status = future.wait_for(std::chrono::seconds(1));
    EXPECT_EQ(status, std::future_status::ready);
}

auto VerifyMesh(std::shared_ptr<engine::Node> root) {
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->Children().size(), 1);

    auto mesh = root->Children()[0]->As<engine::Mesh>();
    EXPECT_NE(mesh->geometry, nullptr);
    EXPECT_NE(mesh->material, nullptr);
    EXPECT_EQ(mesh->geometry->VertexCount(), 4);
    EXPECT_EQ(mesh->geometry->IndexCount(), 6);
}

#pragma endregion

#pragma region Load Mesh Synchronously

TEST(MeshLoader, LoadMeshSynchronous) {
    mesh_loader->Load("assets/plane.obj", [](const auto& result) {
        VerifyMesh(result.value());
    });
}

TEST(MeshLoader, LoadMeshSynchronousInvalidFileType) {
    mesh_loader->Load("assets/invalid_plane.fbx", [](const auto& result) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "Unsupported file type '.fbx'");
    });
}

TEST(MeshLoader, LoadMeshSynchronousInvalidFile) {
    mesh_loader->Load("assets/invalid_plane.obj", [](const auto& result) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "File not found 'assets/invalid_plane.obj'");
    });
}

#pragma endregion

#pragma region Load Mesh Asynchronously

TEST(MeshLoader, LoadMeshAsynchronous) {
    RunAsyncTest("assets/plane.obj", [](const auto& result, const auto& main_thread_id) {
        VerifyMesh(result.value());
        EXPECT_NE(std::this_thread::get_id(), main_thread_id);
    });
}

TEST(MeshLoader, LoadMeshAsynchronousInvalidFileType) {
    RunAsyncTest("assets/invalid_plane.fbx", [](const auto& result, const auto& main_thread_id) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "Unsupported file type '.fbx'");
        EXPECT_NE(std::this_thread::get_id(), main_thread_id);
    });
}

TEST(MeshLoader, LoadMeshAsynchronousInvalidFile) {
    RunAsyncTest("assets/invalid_plane.obj", [](const auto& result, const auto& main_thread_id) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "File not found 'assets/invalid_plane.obj'");
        EXPECT_NE(std::this_thread::get_id(), main_thread_id);
    });
}

#pragma endregion