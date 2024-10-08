// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/color.hpp>

#pragma region Constructors

TEST(Color, ConstructorDefault) {
    auto color = engine::Color {};

    EXPECT_FLOAT_EQ(color.r, 1.0f);
    EXPECT_FLOAT_EQ(color.g, 1.0f);
    EXPECT_FLOAT_EQ(color.b, 1.0f);
    EXPECT_FLOAT_EQ(color.a, 1.0f);
}

TEST(Color, ConstructorRGB) {
    auto color = engine::Color {0.5f, 0.25f, 0.75f};

    EXPECT_FLOAT_EQ(color.r, 0.5f);
    EXPECT_FLOAT_EQ(color.g, 0.25f);
    EXPECT_FLOAT_EQ(color.b, 0.75f);
    EXPECT_FLOAT_EQ(color.a, 1.0f);
}

TEST(Color, ConstructorRGBA) {
    auto color = engine::Color {0.3f, 0.6f, 0.9f, 0.5f};

    EXPECT_FLOAT_EQ(color.r, 0.3f);
    EXPECT_FLOAT_EQ(color.g, 0.6f);
    EXPECT_FLOAT_EQ(color.b, 0.9f);
    EXPECT_FLOAT_EQ(color.a, 0.5f);
}

TEST(Color, ConstructorHex) {
    auto color = engine::Color {0xFF7F50};

    EXPECT_NEAR(color.r, 1.0f, 0.1f);
    EXPECT_NEAR(color.g, 0.4f, 0.1f);
    EXPECT_NEAR(color.b, 0.3f, 0.1f);
    EXPECT_NEAR(color.a, 1.0f, 0.1f);
}

#pragma endregion

#pragma region Operator Overloading

TEST(Color, AssignmentOperatorHex) {
    auto color = engine::Color {};
    color = 0xFF4500;

    EXPECT_NEAR(color.r, 1.0f, 0.1f);
    EXPECT_NEAR(color.g, 0.2f, 0.1f);
    EXPECT_NEAR(color.b, 0.0f, 0.1f);
    EXPECT_NEAR(color.a, 1.0f, 0.1f);
}

#pragma endregion