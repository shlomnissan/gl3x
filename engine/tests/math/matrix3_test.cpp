// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/matrix3.hpp>
#include <engine/math/vector3.hpp>

TEST(Matrix3, DefaultConstructor) {
    auto m = engine::Matrix3 {};

    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            EXPECT_FLOAT_EQ(m(i, j), 0.0f);
        }
    }
}

TEST(Matrix3, SingleParameterConstructor) {
    auto m = engine::Matrix3 {1.0f};

    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(m(0, 2), 0.0f);

    EXPECT_FLOAT_EQ(m(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(m(1, 1), 1.0f);
    EXPECT_FLOAT_EQ(m(1, 2), 0.0f);

    EXPECT_FLOAT_EQ(m(2, 0), 0.0f);
    EXPECT_FLOAT_EQ(m(2, 1), 0.0f);
    EXPECT_FLOAT_EQ(m(2, 2), 1.0f);
}

TEST(Matrix3, ParameterizedConstructor) {
    auto m = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f,
    };

    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 1), 2.0f);
    EXPECT_FLOAT_EQ(m(0, 2), 3.0f);

    EXPECT_FLOAT_EQ(m(1, 0), 4.0f);
    EXPECT_FLOAT_EQ(m(1, 1), 5.0f);
    EXPECT_FLOAT_EQ(m(1, 2), 6.0f);

    EXPECT_FLOAT_EQ(m(2, 0), 7.0f);
    EXPECT_FLOAT_EQ(m(2, 1), 8.0f);
    EXPECT_FLOAT_EQ(m(2, 2), 9.0f);
}

TEST(Matrix3, VectorConstructor) {
    auto m = engine::Matrix3 {
        engine::Vector3 {1.0f, 4.0f, 7.0f},
        engine::Vector3 {2.0f, 5.0f, 8.0f},
        engine::Vector3 {3.0f, 6.0f, 9.0f},
    };

    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 1), 2.0f);
    EXPECT_FLOAT_EQ(m(0, 2), 3.0f);

    EXPECT_FLOAT_EQ(m(1, 0), 4.0f);
    EXPECT_FLOAT_EQ(m(1, 1), 5.0f);
    EXPECT_FLOAT_EQ(m(1, 2), 6.0f);

    EXPECT_FLOAT_EQ(m(2, 0), 7.0f);
    EXPECT_FLOAT_EQ(m(2, 1), 8.0f);
    EXPECT_FLOAT_EQ(m(2, 2), 9.0f);
}