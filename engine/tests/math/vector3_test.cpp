// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/vector3.hpp>

TEST(Vector3, Constructors) {
    // default constructor
    auto v1 = engine::Vector3 {};
    EXPECT_EQ(v1.x, 0.0f);
    EXPECT_EQ(v1.y, 0.0f);
    EXPECT_EQ(v1.z, 0.0f);

    // single parameter
    auto v2 = engine::Vector3 {1.0f};
    EXPECT_EQ(v2.x, 1.0f);
    EXPECT_EQ(v2.y, 1.0f);
    EXPECT_EQ(v2.z, 1.0f);

    // parameterized
    auto v3 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_EQ(v3.x, 1.0f);
    EXPECT_EQ(v3.y, 2.0f);
    EXPECT_EQ(v3.z, 3.0f);
}

TEST(Vector3, DotProduct) {
    // positive values
    auto v1 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    auto v2 = engine::Vector3 {4.0f, 5.0f, 6.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v1, v2), 32.0f);

    // negative values
    auto v3 = engine::Vector3 {-1.0f, -2.0f, -3.0f};
    auto v4 = engine::Vector3 {-4.0f, -5.0f, -6.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v3, v4), 32.0f);

    // mixed values
    auto v5 = engine::Vector3 {-1.0f, 2.0f, -3.0f};
    auto v6 = engine::Vector3 {4.0f, -5.0f, 6.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v5, v6), -32.0f);

    // zero vector
    auto v7 = engine::Vector3 {0.0f, 0.0f, 0.0f};
    auto v8 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v7, v8), 0.0f);

    // large values
    auto v9 = engine::Vector3 {1e6f, 2e6f, 3e6f};
    auto v10 = engine::Vector3 {4e6f, 5e6f, 6e6f};
    EXPECT_FLOAT_EQ(engine::Dot(v9, v10), 3.2e+13);

    // perpendicular vectors
    auto v11 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    auto v12 = engine::Vector3 {0.0f, 1.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v11, v12), 0.0f);

    // parallel vectors
    auto v13 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    auto v14 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v13, v14), 1.0f);

    // opposite direction
    auto v15 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    auto v16 = engine::Vector3 {-1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::Dot(v15, v16), -1.0f);
}