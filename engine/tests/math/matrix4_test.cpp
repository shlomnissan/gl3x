// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/matrix4.hpp>

auto EXPECT_MAT4_EQ(const engine::Matrix4&, const engine::Matrix4&) -> void;

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

auto EXPECT_MAT4_EQ(const engine::Matrix4& a, const engine::Matrix4& b) -> void {
    EXPECT_FLOAT_EQ(a(0, 0), b(0, 0));
    EXPECT_FLOAT_EQ(a(0, 1), b(0, 1));
    EXPECT_FLOAT_EQ(a(0, 2), b(0, 2));
    EXPECT_FLOAT_EQ(a(0, 3), b(0, 3));

    EXPECT_FLOAT_EQ(a(1, 0), b(1, 0));
    EXPECT_FLOAT_EQ(a(1, 1), b(1, 1));
    EXPECT_FLOAT_EQ(a(1, 2), b(1, 2));
    EXPECT_FLOAT_EQ(a(1, 3), b(1, 3));

    EXPECT_FLOAT_EQ(a(2, 0), b(2, 0));
    EXPECT_FLOAT_EQ(a(2, 1), b(2, 1));
    EXPECT_FLOAT_EQ(a(2, 2), b(2, 2));
    EXPECT_FLOAT_EQ(a(2, 3), b(2, 3));

    EXPECT_FLOAT_EQ(a(3, 0), b(3, 0));
    EXPECT_FLOAT_EQ(a(3, 1), b(3, 1));
    EXPECT_FLOAT_EQ(a(3, 2), b(3, 2));
    EXPECT_FLOAT_EQ(a(3, 3), b(3, 3));
}