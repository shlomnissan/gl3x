/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>

#include <vglx/loaders/texture_loader.hpp>

#include <future>
#include <thread>

const auto texture_loader = vglx::TextureLoader::Create();

#pragma region Helpers

template <typename Callback>
auto RunAsyncTest(const std::string& file_path, Callback callback) {
    auto main_thread_id = std::this_thread::get_id();
    auto promise = std::promise<void> {};
    auto future = promise.get_future();

    texture_loader->LoadAsync(file_path, [&](const auto& result) {
        callback(result, main_thread_id);
        promise.set_value();
    });

    auto status = future.wait_for(std::chrono::seconds(1));
    EXPECT_EQ(status, std::future_status::ready);
}

auto VerifyImage(const auto& texture, const std::string& filename) {
    EXPECT_EQ(texture->data.size(), 5 * 5 * 4);
    EXPECT_EQ(texture->width, 5);
    EXPECT_EQ(texture->height, 5);
}

#pragma endregion

#pragma region Load Image Synchronously

TEST(TextureLoader, LoadTextureSynchronous) {
    auto result = texture_loader->Load("assets/texture.tex");
    VerifyImage(result.value(), "texture.tex");
}

TEST(TextureLoader, LoadTextureSynchronousInvalidFileType) {
    auto result = texture_loader->Load("assets/texture.png");
    EXPECT_FALSE(result);
    EXPECT_EQ(result.error(), "Invalid texture file 'assets/texture.png'");
}

TEST(TextureLoader, LoadTextureSynchronousInvalidFile) {
    auto result = texture_loader->Load("assets/invalid_texture.tex");
    EXPECT_FALSE(result);
    EXPECT_EQ(result.error(), "File not found 'assets/invalid_texture.tex'");
}

#pragma endregion

#pragma region Load Image Asynchronously

TEST(TextureLoader, LoadTextureAsynchronous) {
    RunAsyncTest("assets/texture.tex", [](const auto& result, const auto& main_thread_id) {
        VerifyImage(result.value(), "texture.tex");
        EXPECT_NE(main_thread_id, std::this_thread::get_id());
    });
}

TEST(TextureLoader, LoadTextureAsynchronousInvalidFileType) {
    RunAsyncTest("assets/texture.png", [](const auto& result, const auto& main_thread_id) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "Invalid texture file 'assets/texture.png'");
        EXPECT_NE(main_thread_id, std::this_thread::get_id());
    });
}

#pragma endregion