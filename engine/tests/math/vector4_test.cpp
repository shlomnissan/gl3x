// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/vector4.hpp>

TEST(Vector4, DefaultConstructor) {
    // default constructor
    auto v1 = engine::Vector4 {};
    EXPECT_EQ(v1.x, 0.0f);
    EXPECT_EQ(v1.y, 0.0f);
    EXPECT_EQ(v1.z, 0.0f);
    EXPECT_EQ(v1.w, 0.0f);

    // single parameter
    auto v2 = engine::Vector4 {1.0f};
    EXPECT_EQ(v2.x, 1.0f);
    EXPECT_EQ(v2.y, 1.0f);
    EXPECT_EQ(v2.z, 1.0f);
    EXPECT_EQ(v2.w, 1.0f);

    // parameterized
    auto v3 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0};
    EXPECT_EQ(v3.x, 1.0f);
    EXPECT_EQ(v3.y, 2.0f);
    EXPECT_EQ(v3.z, 3.0f);
    EXPECT_EQ(v3.w, 4.0f);
}

TEST(Vector4, DotProduct) {
    // positive values
    auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    auto v2 = engine::Vector4 {4.0f, 5.0f, 6.0f, 7.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v1, v2), 60.0f);

    // negative values
    auto v3 = engine::Vector4 {-1.0f, -2.0f, -3.0f, -4.0f};
    auto v4 = engine::Vector4 {-4.0f, -5.0f, -6.0f, -7.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v3, v4), 60.0f);

    // mixed values
    auto v5 = engine::Vector4 {-1.0f, 2.0f, -3.0f, 4.0f};
    auto v6 = engine::Vector4 {4.0f, -5.0f, 6.0f, -7.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v5, v6), -60.0f);

    // zero vector
    auto v7 = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};
    auto v8 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v7, v8), 0.0f);

    // large values
    auto v9 = engine::Vector4 {1e6f, 2e6f, 3e6f, 4e6f};
    auto v10 = engine::Vector4 {4e6f, 5e6f, 6e6f, 7e6f};
    EXPECT_FLOAT_EQ(engine::Dot(v9, v10), 6e+13);

    // perpendicular vectors
    auto v11 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    auto v12 = engine::Vector4 {0.0f, 1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v11, v12), 0.0f);

    // parallel vectors
    auto v13 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    auto v14 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v13, v14), 1.0f);

    // opposite direction
    auto v15 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    auto v16 = engine::Vector4 {-1.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v15, v16), -1.0f);
}