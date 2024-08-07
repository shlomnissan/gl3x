// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/matrix3.hpp>

auto EXPECT_MAT3_EQ(const engine::Matrix3&, const engine::Matrix3&) -> void;

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

auto EXPECT_MAT3_EQ(const engine::Matrix3& a, const engine::Matrix3& b) -> void {
    EXPECT_FLOAT_EQ(a(0, 0), b(0, 0));
    EXPECT_FLOAT_EQ(a(0, 1), b(0, 1));
    EXPECT_FLOAT_EQ(a(0, 2), b(0, 2));

    EXPECT_FLOAT_EQ(a(1, 0), b(1, 0));
    EXPECT_FLOAT_EQ(a(1, 1), b(1, 1));
    EXPECT_FLOAT_EQ(a(1, 2), b(1, 2));

    EXPECT_FLOAT_EQ(a(2, 0), b(2, 0));
    EXPECT_FLOAT_EQ(a(2, 1), b(2, 1));
    EXPECT_FLOAT_EQ(a(2, 2), b(2, 2));
}