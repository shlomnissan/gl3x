// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/loaders/image_loader.hpp>

#include <future>
#include <thread>

const auto image_loader = engine::ImageLoader::Create();

#pragma region Helpers

template <typename Callback>
auto RunAsyncTest(const std::string& file_path, Callback callback) {
    auto main_thread_id = std::this_thread::get_id();
    auto promise = std::promise<void> {};
    auto future = promise.get_future();

    image_loader->LoadAsync(file_path, [&](const auto& result) {
        callback(result, main_thread_id);
        promise.set_value();
    });

    auto status = future.wait_for(std::chrono::seconds(1));
    EXPECT_EQ(status, std::future_status::ready);
}

auto VerifyImage(const auto& image, const std::string& filename) {
    EXPECT_NE(image, nullptr);
    EXPECT_EQ(image->data.size(), 5 * 5 * 4);
    EXPECT_EQ(image->width, 5);
    EXPECT_EQ(image->height, 5);
    EXPECT_EQ(image->channels, 4);
    EXPECT_EQ(image->filename, filename);
}

#pragma endregion

#pragma region Load Image Synchronously

TEST(ImageLoader, LoadImageSynchronous) {
    image_loader->Load("assets/texture.tex", [](const auto& result) {
        VerifyImage(result.value(), "texture.tex");
    });
}

TEST(ImageLoader, LoadImageSynchronousInvalidFileType) {
    image_loader->Load("assets/invalid_texture.png", [](const auto& result) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "Unsupported file type '.png'");
    });
}

TEST(ImageLoader, LoadImageSynchronousInvalidFile) {
    image_loader->Load("assets/invalid_texture.tex", [](const auto& result) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "File not found 'assets/invalid_texture.tex'");
    });
}

#pragma endregion

#pragma region Load Image Asynchronously

TEST(ImageLoader, LoadImageAsynchronous) {
    RunAsyncTest("assets/texture.tex", [](const auto& result, const auto& main_thread_id) {
        VerifyImage(result.value(), "texture.tex");
        EXPECT_NE(main_thread_id, std::this_thread::get_id());
    });
}

TEST(ImageLoader, LoadImageAsynchronousInvalidFileType) {
    RunAsyncTest("assets/invalid_texture.png", [](const auto& result, const auto& main_thread_id) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "Unsupported file type '.png'");
        EXPECT_NE(main_thread_id, std::this_thread::get_id());
    });
}

TEST(ImageLoader, LoadImageAsynchronousInvalidFile) {
    RunAsyncTest("assets/invalid_texture.tex", [](const auto& result, const auto& main_thread_id) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "File not found 'assets/invalid_texture.tex'");
        EXPECT_NE(main_thread_id, std::this_thread::get_id());
    });
}

#pragma endregion