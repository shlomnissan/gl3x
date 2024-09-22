// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <memory>

#include <engine/core/image.hpp>

#pragma Constructors

TEST(ImageTest, ConstructWithValidData) {
    auto data = new unsigned char[3] {255, 128, 64};

    auto image = engine::Image {{
        .width = 1,
        .height = 1,
        .depth = 3
    }, engine::ImageDataPtr(data, [](void*){})};

    EXPECT_EQ(image.Data()[0], 255);
    EXPECT_EQ(image.Data()[1], 128);
    EXPECT_EQ(image.Data()[2], 64);
}

#pragma endregion