// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/loaders/image_loader.hpp>

#include <future>
#include <thread>

const auto image_loader = engine::ImageLoader {};

#pragma region Load Image Synchronously

TEST(ImageLoader, LoadImageSynchronous) {
    image_loader.Load("assets/texture.png", [](std::shared_ptr<engine::Image> image) {
        EXPECT_NE(image, nullptr);
        EXPECT_NE(image->Data(), nullptr);

        EXPECT_EQ(image->Width(), 5);
        EXPECT_EQ(image->Height(), 5);
        EXPECT_EQ(image->Depth(), 4);
        EXPECT_EQ(image->Filename(), "texture.png");
    });
}

#pragma endregion

#pragma region Load Image Asynchronously

TEST(ImageLoader, LoadImageAsynchronous) {
    auto main_thread_id = std::this_thread::get_id();
    auto promise = std::promise<void> {};
    auto future = promise.get_future();

    image_loader.LoadAsync("assets/texture.png", [&](std::shared_ptr<engine::Image> image) {
        EXPECT_NE(image, nullptr);
        EXPECT_NE(image->Data(), nullptr);
        EXPECT_NE(main_thread_id, std::this_thread::get_id());

        EXPECT_EQ(image->Width(), 5);
        EXPECT_EQ(image->Height(), 5);
        EXPECT_EQ(image->Depth(), 4);
        EXPECT_EQ(image->Filename(), "texture.png");

        promise.set_value();
    });

    auto status = future.wait_for(std::chrono::seconds(5));
    EXPECT_EQ(status, std::future_status::ready);
}

#pragma endregion