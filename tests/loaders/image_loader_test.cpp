// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include "engine/loaders/image_loader.hpp"

#pragma Load Image

TEST(ImageLoaderTest, LoadImageWithValidPath) {
    auto image = engine::ImageLoader::Load("assets/texture.png").value();

    EXPECT_EQ(image.Width(), 5);
    EXPECT_EQ(image.Height(), 5);
    EXPECT_EQ(image.Depth(), 4);
}

TEST(ImageLoaderTest, LoadImageWithInvalidPath) {
    auto invalid_image = engine::ImageLoader::Load("invalid_path/image.png");

    EXPECT_FALSE(invalid_image);
}

#pragma endregion