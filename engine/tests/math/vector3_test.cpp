// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/vector3.hpp>

TEST(Vector3, DefaultConstructor) {
    auto vec = engine::Vector3 {};

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.y, 0.0f);
    EXPECT_EQ(vec.z, 0.0f);
}

TEST(Vector3, SingleParameterConstructor) {
    auto vec = engine::Vector3 {1.0f};

    EXPECT_EQ(vec.x, 1.0f);
    EXPECT_EQ(vec.y, 1.0f);
    EXPECT_EQ(vec.z, 1.0f);
}

TEST(Vector3, ParameterizedConstructor) {
    auto vec = engine::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_EQ(vec.x, 1.0f);
    EXPECT_EQ(vec.y, 2.0f);
    EXPECT_EQ(vec.z, 3.0f);
}