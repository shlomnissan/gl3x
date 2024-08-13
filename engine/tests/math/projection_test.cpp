// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/projection.hpp>

TEST(Projection, Orthographic) {
    // standard viewport
    const auto m1 = engine::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 0.0f);
    EXPECT_MAT4_EQ(m1, {
        1.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 1.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    });

    // screen space
    const auto m2 = engine::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    EXPECT_MAT4_NEAR(m2, {
        0.0024f, 0.0000f,  0.0000f, -1.0000f,
        0.0000f, 0.0033f,  0.0000f, -1.0000f,
        0.0000f, 0.0000f, -0.0200f, -1.0020f,
        0.0000f, 0.0000f,  0.0000f,  1.0000f
    }, 0.001f);

    // positive near-far planes
    const auto m3 = engine::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 1.5f);
    EXPECT_MAT4_EQ(m3, {
        1.0f, 0.0f,  0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,  0.0f,
        0.0f, 0.0f, -2.0f, -2.0f,
        0.0f, 0.0f,  0.0f,  1.0f
    });
}