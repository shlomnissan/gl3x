// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/loaders/image_loader.hpp>

#include <future>
#include <thread>

const auto image_loader = engine::ImageLoader {};

#pragma region Helpers

template <typename Callback>
auto RunAsyncTest(const std::string& file_path, Callback callback) {
    auto main_thread_id = std::this_thread::get_id();
    auto promise = std::promise<void> {};
    auto future = promise.get_future();

    image_loader.LoadAsync(file_path, [&](const auto& result) {
        callback(result, main_thread_id);
        promise.set_value();
    });

    auto status = future.wait_for(std::chrono::seconds(1));
    EXPECT_EQ(status, std::future_status::ready);
}

auto VerifyImage(
    const auto& image,
    const auto& filename,
    const auto width,
    const auto height,
    const auto depth
) {
    EXPECT_NE(image, nullptr);
    EXPECT_NE(image->Data(), nullptr);

    EXPECT_EQ(image->width, 5);
    EXPECT_EQ(image->height, 5);
    EXPECT_EQ(image->depth, 4);
    EXPECT_EQ(image->filename, filename);
}

#pragma endregion

#pragma region Load Image Synchronously

TEST(ImageLoader, LoadImageSynchronous) {
    image_loader.Load("assets/texture.png", [](const auto& result) {
        VerifyImage(result.value(), "texture.png", 5, 5, 4);
    });
}

TEST(ImageLoader, LoadImageSynchronousInvalidFileType) {
    image_loader.Load("assets/invalid_texture.bmp", [](const auto& result) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "Unsupported file type '.bmp'");
    });
}

TEST(ImageLoader, LoadImageSynchronousInvalidFile) {
    image_loader.Load("assets/invalid_texture.png", [](const auto& result) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "File not found 'assets/invalid_texture.png'");
    });
}

#pragma endregion

#pragma region Load Image Asynchronously

TEST(ImageLoader, LoadImageAsynchronous) {
    RunAsyncTest("assets/texture.png", [](const auto& result, const auto& main_thread_id) {
        VerifyImage(result.value(), "texture.png", 5, 5, 4);
    });
}

TEST(ImageLoader, LoadImageAsynchronousInvalidFileType) {
    RunAsyncTest("assets/invalid_texture.bmp", [](const auto& result, const auto& main_thread_id) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "Unsupported file type '.bmp'");
        EXPECT_NE(main_thread_id, std::this_thread::get_id());
    });
}

TEST(ImageLoader, LoadImageAsynchronousInvalidFile) {
    RunAsyncTest("assets/invalid_texture.png", [](const auto& result, const auto& main_thread_id) {
        EXPECT_FALSE(result);
        EXPECT_EQ(result.error(), "File not found 'assets/invalid_texture.png'");
        EXPECT_NE(main_thread_id, std::this_thread::get_id());
    });
}

#pragma endregion