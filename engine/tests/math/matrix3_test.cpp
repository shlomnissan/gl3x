// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix3.hpp>

TEST(Matrix3, Constructors) {
    // default constructor
    auto m1 = engine::Matrix3 {};
    EXPECT_MAT3_EQ(m1, {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    });

    // single parameter (diagonal matrix)
    auto m2 = engine::Matrix3 {1.0f};
    EXPECT_MAT3_EQ(m2, {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });

    // parameterized
    auto m3 = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    EXPECT_MAT3_EQ(m3, {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });

    // vector initialization
    auto m4 = engine::Matrix3 {
        engine::Vector3 {1.0f, 4.0f, 7.0f},
        engine::Vector3 {2.0f, 5.0f, 8.0f},
        engine::Vector3 {3.0f, 6.0f, 9.0f},
    };
    EXPECT_MAT3_EQ(m4, {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });
}

TEST(Matrix3, MatrixMultiplication) {
    auto m1 = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    auto m2 = engine::Matrix3 {
        1.0f, 5.0f, 1.0f,
        2.0f, 1.0f, 3.0f,
        1.0f, 5.0f, 4.0f
    };

    EXPECT_MAT3_EQ((m1 * m2), {
         8.0f, 22.0f, 19.0f,
        24.0f, 66.0f, 51.0f,
        12.0f, 33.0f, 21.0f,
    });
}