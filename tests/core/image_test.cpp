// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include "engine/core/image.hpp"

#pragma Constructors

TEST(ImageTest, ConstructWithValidData) {
    auto data = engine::ImageData {255, 128, 64};
    auto image = engine::Image {{
        .width = 2,
        .height = 2,
        .depth = 4,
        .flipped = true
    }, data};

    EXPECT_EQ(image.Data().size(), 3);
}

TEST(ImageTest, ConstructWithRValueReference) {
    auto data = engine::ImageData {255, 128, 64};
    auto image = engine::Image {{
        .width = 2,
        .height = 2,
        .depth = 4,
        .flipped = true
    }, std::move(data)};

    EXPECT_EQ(data.size(), 0); // the data was moved
    EXPECT_EQ(image.Data().size(), 3);
}

TEST(ImageTest, ConstructWithEmptyData) {
    auto image = engine::Image {{
        .width = 2,
        .height = 2,
        .depth = 4,
        .flipped = true
    }, {}};

    EXPECT_TRUE(image.Data().empty());
}

#pragma endregion