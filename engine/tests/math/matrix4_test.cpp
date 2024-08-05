// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/matrix4.hpp>

TEST(Matrix4, ParameterizedConstructor) {
    auto m = engine::Matrix4 {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 1), 2.0f);
    EXPECT_FLOAT_EQ(m(0, 2), 3.0f);
    EXPECT_FLOAT_EQ(m(0, 3), 4.0f);

    EXPECT_FLOAT_EQ(m(1, 0), 5.0f);
    EXPECT_FLOAT_EQ(m(1, 1), 6.0f);
    EXPECT_FLOAT_EQ(m(1, 2), 7.0f);
    EXPECT_FLOAT_EQ(m(1, 3), 8.0f);

    EXPECT_FLOAT_EQ(m(2, 0), 9.0f);
    EXPECT_FLOAT_EQ(m(2, 1), 10.0f);
    EXPECT_FLOAT_EQ(m(2, 2), 11.0f);
    EXPECT_FLOAT_EQ(m(2, 3), 12.0f);

    EXPECT_FLOAT_EQ(m(3, 0), 13.0f);
    EXPECT_FLOAT_EQ(m(3, 1), 14.0f);
    EXPECT_FLOAT_EQ(m(3, 2), 15.0f);
    EXPECT_FLOAT_EQ(m(3, 3), 16.0f);
}