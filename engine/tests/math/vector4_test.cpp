// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/vector4.hpp>

TEST(Vector4, DefaultConstructor) {
    auto vec = engine::Vector4 {};

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.y, 0.0f);
    EXPECT_EQ(vec.z, 0.0f);
    EXPECT_EQ(vec.w, 0.0f);
}

TEST(Vector4, SingleParameterConstructor) {
    auto vec = engine::Vector4 {1.0f};

    EXPECT_EQ(vec.x, 1.0f);
    EXPECT_EQ(vec.y, 1.0f);
    EXPECT_EQ(vec.z, 1.0f);
    EXPECT_EQ(vec.w, 1.0f);
}

TEST(Vector4, ParameterizedConstructor) {
    auto vec = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0};

    EXPECT_EQ(vec.x, 1.0f);
    EXPECT_EQ(vec.y, 2.0f);
    EXPECT_EQ(vec.z, 3.0f);
    EXPECT_EQ(vec.w, 4.0f);
}