// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include <engine/math/color.hpp>

#pragma region Constructors

TEST(Color, ConstructorDefault) {
    auto color = engine::Color {};

    EXPECT_FLOAT_EQ(color.r, 1.0f);
    EXPECT_FLOAT_EQ(color.g, 1.0f);
    EXPECT_FLOAT_EQ(color.b, 1.0f);
}

TEST(Color, ConstructorRGB) {
    auto color = engine::Color {0.5f, 0.25f, 0.75f};

    EXPECT_FLOAT_EQ(color.r, 0.5f);
    EXPECT_FLOAT_EQ(color.g, 0.25f);
    EXPECT_FLOAT_EQ(color.b, 0.75f);
}

TEST(Color, ConstructorHex) {
    auto color = engine::Color {0xFF7F50};

    EXPECT_NEAR(color.r, 1.0f, 0.1f);
    EXPECT_NEAR(color.g, 0.4f, 0.1f);
    EXPECT_NEAR(color.b, 0.3f, 0.1f);
}

#pragma endregion

#pragma region Component Access

TEST(Color, ComponentAccessDirect) {
    const auto c = engine::Color {0xFF7F50};

    EXPECT_NEAR(c.r, 1.0f, 0.1f);
    EXPECT_NEAR(c.g, 0.4f, 0.1f);
    EXPECT_NEAR(c.b, 0.3f, 0.1f);
}

TEST(Color, ComponentAccessRandomAccessOperator) {
    const auto c = engine::Color {0xFF7F50};

    EXPECT_NEAR(c[0], 1.0f, 0.1f);
    EXPECT_NEAR(c[1], 0.4f, 0.1f);
    EXPECT_NEAR(c[2], 0.3f, 0.1f);
    EXPECT_DEATH({ (void)c[3]; }, ".*i >= 0 && i < 3.*");
}

#pragma endregion

#pragma region Assignment Operator

TEST(Color, AssignmentOperatorHex) {
    auto color = engine::Color {};
    color = 0xFF4500;

    EXPECT_NEAR(color.r, 1.0f, 0.1f);
    EXPECT_NEAR(color.g, 0.2f, 0.1f);
    EXPECT_NEAR(color.b, 0.0f, 0.1f);
}

#pragma endregion

#pragma region Equality Operator

TEST(Color, EqualityOperator) {
    const auto c1 = engine::Color {0xFFAD69};
    const auto c2 = engine::Color {0xFFAD69};
    const auto c3 = engine::Color {0x47A8BD};

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
}

TEST(Color, InequalityOperator) {
    const auto c1 = engine::Color {0xFFAD69};
    const auto c2 = engine::Color {0xFFAD69};
    const auto c3 = engine::Color {0x47A8BD};

    EXPECT_FALSE(c1 != c2);
    EXPECT_TRUE(c1 != c3);
}

#pragma endregion

#pragma region Scalar Multiplication

TEST(Color, ScalarMultiplication) {
    const auto c = engine::Color {0.2f, 0.4f, 0.6f} * 2.0f;

    EXPECT_FLOAT_EQ(c.r, 0.4f);
    EXPECT_FLOAT_EQ(c.g, 0.8f);
    EXPECT_FLOAT_EQ(c.b, 1.0f); // Clamped to 1.0f
}


TEST(Color, ScalarMultiplicationInPlace) {
    auto c = engine::Color {0.2f, 0.4f, 0.6f};
    c *= 2.0f;

    EXPECT_FLOAT_EQ(c.r, 0.4f);
    EXPECT_FLOAT_EQ(c.g, 0.8f);
    EXPECT_FLOAT_EQ(c.b, 1.0f); // Clamped to 1.0f
}

#pragma endregion