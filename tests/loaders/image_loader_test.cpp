// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/loaders/image_loader.hpp>

const auto image_loader = engine::ImageLoader {};

#pragma region Load Image

TEST(ImageLoader, LoadImage) {
    image_loader.Load("assets/texture.png", [](std::shared_ptr<engine::Image> image) {
        EXPECT_EQ(image->Width(), 5);
        EXPECT_EQ(image->Height(), 5);
        EXPECT_EQ(image->Depth(), 4);
        EXPECT_EQ(image->Filename(), "texture.png");
        EXPECT_NE(image->Data(), nullptr);
    });
}

#pragma endregion