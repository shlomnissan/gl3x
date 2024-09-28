// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/textures/texture_2d.hpp>

#pragma Constructors

TEST(Texture2DTest, InitTexture) {
    auto texture = engine::Texture2D("assets/texture.png");

    EXPECT_TRUE(texture.Loaded());
    EXPECT_NE(texture.Image().Data(), nullptr);
    EXPECT_EQ(texture.Image().Width(), 5);
    EXPECT_EQ(texture.Image().Height(), 5);
    EXPECT_EQ(texture.Image().Depth(), 4);
}

TEST(Texture2DTest, InitTextureWithInvalidPath) {
    auto texture = engine::Texture2D("invalid_path/image.png");

    EXPECT_FALSE(texture.Loaded());
    EXPECT_EQ(texture.Image().Data(), nullptr);
    EXPECT_EQ(texture.Image().Width(), 0);
    EXPECT_EQ(texture.Image().Height(), 0);
    EXPECT_EQ(texture.Image().Depth(), 0);
}

#pragma endregion