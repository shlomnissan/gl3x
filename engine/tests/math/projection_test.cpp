// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/projection.hpp>

TEST(ProjectionOrthographic, StandardViewport) {
    const auto m = engine::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 0.0f);

    EXPECT_MAT4_EQ(m, {
        1.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 1.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    });
}

TEST(ProjectionOrthographic, ScreenSpace) {
    const auto m = engine::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    EXPECT_MAT4_NEAR(m, {
        0.0024f, 0.0000f,  0.0000f, -1.0000f,
        0.0000f, 0.0033f,  0.0000f, -1.0000f,
        0.0000f, 0.0000f, -0.0200f, -1.0020f,
        0.0000f, 0.0000f,  0.0000f,  1.0000f
    }, 0.001f);
}

TEST(ProjectionOrthographic, PositiveNearFarPlanes) {
    const auto m = engine::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 1.5f);

    EXPECT_MAT4_EQ(m, {
        1.0f, 0.0f,  0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,  0.0f,
        0.0f, 0.0f, -2.0f, -2.0f,
        0.0f, 0.0f,  0.0f,  1.0f
    });
}