// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/loaders/image_loader.hpp>

#pragma region Load

TEST(ImageLoader, LoadBasic) {
    auto image_loader = engine::ImageLoader {"assets/texture.png"};

    image_loader.Load([](std::shared_ptr<engine::Image> image) {
        EXPECT_EQ(image->Width(), 5);
        EXPECT_EQ(image->Height(), 5);
        EXPECT_EQ(image->Depth(), 4);
        EXPECT_EQ(image->Filename(), "texture.png");
        EXPECT_NE(image->Data(), nullptr);
    });
}

#pragma endregion