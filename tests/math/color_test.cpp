// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/color.hpp>

#pragma region Constructors

TEST(Color, ConstructorDefault) {
    auto color = engine::Color {};

    EXPECT_COLOR_EQ(color, 0xFFFFFF);
}

TEST(Color, ConstructorRGB) {
    auto color = engine::Color {0.5f, 0.25f, 0.75f};

    EXPECT_COLOR_EQ(color, {0.5f, 0.25f, 0.75f});
}

TEST(Color, ConstructorHex) {
    auto color = engine::Color {0xFF7F50};

    EXPECT_COLOR_NEAR(color, {1.0f, 0.4f, 0.3f}, 0.1f);
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
    auto color = engine::Color {0.1f, 0.1f, 0.1f};
    color = 0xFF4500;

    EXPECT_COLOR_NEAR(color, {1.0f, 0.27f, 0.0f}, 0.1f);
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

#pragma region Addition

TEST(Color, AdditionBasic) {
    const auto c1 = engine::Color {0.2f, 0.4f, 0.6f};
    const auto c2 = engine::Color {0.1f, 0.2f, 0.3f};

    EXPECT_COLOR_EQ(c1 + c2, {0.3f, 0.6f, 0.9f});
}

TEST(Color, AdditionBlackColor) {
    const auto c = engine::Color {0.2f, 0.4f, 0.6f};
    const auto black = engine::Color {0x000000};

    EXPECT_COLOR_EQ(c + black, {0.2f, 0.4f, 0.6f});
}

#pragma endregion

#pragma region Subtraction

TEST(Color, SubtractionBasic) {
    const auto c1 = engine::Color {0.5f, 0.7f, 0.9f};
    const auto c2 = engine::Color {0.2f, 0.3f, 0.4f};

    EXPECT_COLOR_EQ(c1 - c2, {0.3f, 0.4f, 0.5f});
}

TEST(Color, SubtractionWithBlackColor) {
    const auto c = engine::Color {0.5f, 0.7f, 0.9f};
    const auto black = engine::Color {0x000000};

    EXPECT_COLOR_EQ(c - black, {0.5f, 0.7f, 0.9f});
}

TEST(Color, SubtractionFromSelf) {
    const auto c = engine::Color {0.5f, 0.7f, 0.9f};

    EXPECT_COLOR_EQ(c - c, 0x000000);
}

TEST(Color, SubtractionResultingInClamping) {
    const auto c1 = engine::Color {0.1f, 0.2f, 0.3f};
    const auto c2 = engine::Color {0.2f, 0.3f, 0.4f};
    const auto result = c1 - c2;

    EXPECT_COLOR_EQ(result, {0.0f, 0.0f, 0.0f});
}

#pragma endregion

#pragma region Multiplication

TEST(Color, ScalarMultiplication) {
    const auto c = engine::Color {0.2f, 0.4f, 0.6f} * 2.0f;

    EXPECT_COLOR_EQ(c, {0.4f, 0.8f, 1.2f});
}


TEST(Color, ScalarMultiplicationInPlace) {
    auto c = engine::Color {0.2f, 0.4f, 0.6f};
    c *= 2.0f;

    EXPECT_COLOR_EQ(c, {0.4f, 0.8f, 1.2f});
}

#pragma endregion

#pragma region Lerp

TEST(Color, Lerp) {
    const auto c1 = engine::Color {0.0f, 0.0f, 0.0f};
    const auto c2 = engine::Color {1.0f, 1.0f, 1.0f};

    EXPECT_COLOR_EQ(engine::Lerp(c1, c2, 0.5f), {0.5f, 0.5f, 0.5f});
}

TEST(Color, LerpZeroFactor) {
    const auto c1 = engine::Color {0.5f, 0.5f, 0.5f};
    const auto c2 = engine::Color {1.0f, 1.0f, 1.0f};

    EXPECT_COLOR_EQ(engine::Lerp(c1, c2, 0.0f), c1);
}

TEST(Color, LerpOneFactor) {
    const auto c1 = engine::Color {0.5f, 0.5f, 0.5f};
    const auto c2 = engine::Color {1.0f, 1.0f, 1.0f};

    EXPECT_COLOR_EQ(engine::Lerp(c1, c2, 1.0f), c2);
}

#pragma endregion