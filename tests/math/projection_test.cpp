// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <numbers>

#include <engine/math/projection.hpp>

constexpr auto pi_4 = std::numbers::pi / 4;

#pragma region Orthographic Projection

TEST(Projection, OrthographicStandardViewport) {
    const auto m = engine::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 0.0f);

    EXPECT_MAT4_EQ(m, {
        1.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 1.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    });
}

TEST(Projection, OrthographicScreenSpace) {
    const auto m = engine::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    EXPECT_MAT4_NEAR(m, {
        0.0024f, 0.0000f,  0.0000f, -1.0000f,
        0.0000f, 0.0033f,  0.0000f, -1.0000f,
        0.0000f, 0.0000f, -0.0200f, -1.0020f,
        0.0000f, 0.0000f,  0.0000f,  1.0000f
    }, 0.001f);
}

TEST(Projection, OrthographicPositiveNearFarPlanes) {
    const auto m = engine::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 1.5f);

    EXPECT_MAT4_EQ(m, {
        1.0f, 0.0f,  0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,  0.0f,
        0.0f, 0.0f, -2.0f, -2.0f,
        0.0f, 0.0f,  0.0f,  1.0f
    });
}

#pragma endregion

#pragma region Perspective Projection

TEST(Projection, PerspectiveStandardViewport) {
    const auto m = engine::perspective(pi_4, 1.0f, 0.1f, 100.0f);

    EXPECT_MAT4_NEAR(m, {
        2.4142f, 0.0000f,  0.0000f,  0.0000f,
        0.0000f, 2.4142f,  0.0000f,  0.0000f,
        0.0000f, 0.0000f, -1.0020f, -0.2002f,
        0.0000f, 0.0000f, -1.0000f,  0.0000f
    }, 0.001f);
}

TEST(Projection, PerspectiveWideAspectRatio) {
    const auto m = engine::perspective(pi_4, 2.0f, 0.1f, 100.0f);

    EXPECT_MAT4_NEAR(m, {
        1.2071f, 0.0000f,  0.0000f,  0.0000f,
        0.0000f, 2.4142f,  0.0000f,  0.0000f,
        0.0000f, 0.0000f, -1.0020f, -0.2002f,
        0.0000f, 0.0000f, -1.0000f,  0.0000f
    }, 0.001f);
}

TEST(Projection, PerspectiveTallAspectRatio) {
    const auto m = engine::perspective(pi_4, 0.5f, 0.1f, 100.0f);

    EXPECT_MAT4_NEAR(m, {
        4.8284f, 0.0000f,  0.0000f,  0.0000f,
        0.0000f, 2.4142f,  0.0000f,  0.0000f,
        0.0000f, 0.0000f, -1.0020f, -0.2002f,
        0.0000f, 0.0000f, -1.0000f,  0.0000f
    }, 0.001f);
}

#pragma endregion