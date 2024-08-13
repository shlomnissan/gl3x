// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix4.hpp>

TEST(Matrix4, Constructors) {
    // default constructor
    auto m1 = engine::Matrix4 {};
    EXPECT_MAT4_EQ(m1, {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    });

    // single parameter (diagonal matrix)
    auto m2 = engine::Matrix4 {1.0f};
    EXPECT_MAT4_EQ(m2, {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    // parameterized
    auto m3 = engine::Matrix4 {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    EXPECT_MAT4_EQ(m3, {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    });

    // vector initialization
    auto m4 = engine::Matrix4 {
        engine::Vector4 {1.0f, 5.0f,  9.0f, 13.0f},
        engine::Vector4 {2.0f, 6.0f, 10.0f, 14.0f},
        engine::Vector4 {3.0f, 7.0f, 11.0f, 15.0f},
        engine::Vector4 {4.0f, 8.0f, 12.0f, 16.0f}
    };
    EXPECT_MAT4_EQ(m4, {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    });
}

TEST(Matrix4, MatrixMultiplication) {
    auto m1 = engine::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };

    auto m2 = engine::Matrix4 {
        1.0f, 5.0f, 1.0f, 8.0f,
        2.0f, 1.0f, 3.0f, 1.0f,
        1.0f, 5.0f, 4.0f, 2.0f,
        9.0f, 6.0f, 1.0f, 3.0f
    };

    EXPECT_MAT4_EQ((m1 * m2), {
        44.0f,  46.0f, 23.0f, 28.0f,
        96.0f, 114.0f, 59.0f, 84.0f,
        21.0f,  39.0f, 22.0f, 42.0f,
        73.0f, 107.0f, 58.0f, 98.0f
    });
}