/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <cassert>

#include <gleam/math/color.hpp>

#pragma region Constructors

TEST(Color, ConstructorDefault) {
    constexpr auto c = gleam::Color {};

    EXPECT_COLOR_EQ(c, 0xFFFFFF);

    static_assert(c == gleam::Color {0xFFFFFF});
}

TEST(Color, ConstructorRGB) {
    constexpr auto c = gleam::Color {0.5f, 0.25f, 0.75f};

    EXPECT_COLOR_EQ(c, {0.5f, 0.25f, 0.75f});

    static_assert(c == gleam::Color {0.5f, 0.25f, 0.75f});
}

TEST(Color, ConstructorHex) {
    constexpr auto c = gleam::Color {0xFF7F50};

    EXPECT_COLOR_NEAR(c, {1.0f, 0.4f, 0.3f}, 0.1f);

    static_assert(ApproxEqual(c.r, 1.0f, 0.1f));
    static_assert(ApproxEqual(c.g, 0.4f, 0.1f));
    static_assert(ApproxEqual(c.b, 0.3f, 0.1f));
}

#pragma endregion

#pragma region Component Access

TEST(Color, ComponentAccessDirect) {
    constexpr auto c = gleam::Color {0xFF7F50};

    EXPECT_NEAR(c.r, 1.0f, 0.1f);
    EXPECT_NEAR(c.g, 0.4f, 0.1f);
    EXPECT_NEAR(c.b, 0.3f, 0.1f);

    static_assert(ApproxEqual(c.r, 1.0f, 0.1f));
    static_assert(ApproxEqual(c.g, 0.4f, 0.1f));
    static_assert(ApproxEqual(c.b, 0.3f, 0.1f));
}

TEST(Color, ComponentAccessRandomAccessOperator) {
    constexpr auto c = gleam::Color {0xFF7F50};

    EXPECT_NEAR(c[0], 1.0f, 0.1f);
    EXPECT_NEAR(c[1], 0.4f, 0.1f);
    EXPECT_NEAR(c[2], 0.3f, 0.1f);

    static_assert(ApproxEqual(c.r, 1.0f, 0.1f));
    static_assert(ApproxEqual(c.g, 0.4f, 0.1f));
    static_assert(ApproxEqual(c.b, 0.3f, 0.1f));
}

#pragma endregion

#pragma region Assignment Operator

TEST(Color, AssignmentOperatorHex) {
    auto c1 = gleam::Color {0.1f, 0.1f, 0.1f};
    c1 = 0xFF4500;

    EXPECT_COLOR_NEAR(c1, {1.0f, 0.27f, 0.0f}, 0.1f);

    // Compile-time check
    constexpr auto c2 = []() {
        auto c = gleam::Color {0.1f, 0.1f, 0.1f};
        c = 0xFF4500;
        return c;
    }();

    static_assert(c2 == gleam::Color {0xFF4500});
}

#pragma endregion

#pragma region Equality Operator

TEST(Color, EqualityOperator) {
    constexpr auto c1 = gleam::Color {0xFFAD69};
    constexpr auto c2 = gleam::Color {0xFFAD69};
    constexpr auto c3 = gleam::Color {0x47A8BD};

    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c1 == c3);

    static_assert(c1 == c2);
    static_assert(c1 != c3);
}

TEST(Color, InequalityOperator) {
    constexpr auto c1 = gleam::Color {0xFFAD69};
    constexpr auto c2 = gleam::Color {0xFFAD69};
    constexpr auto c3 = gleam::Color {0x47A8BD};

    EXPECT_FALSE(c1 != c2);
    EXPECT_TRUE(c1 != c3);

    static_assert(c1 == c2);
    static_assert(c1 != c3);
}

#pragma endregion

#pragma region Addition

TEST(Color, AdditionBasic) {
    constexpr auto c1 = gleam::Color {0.2f, 0.2f, 0.4f};
    constexpr auto c2 = gleam::Color {0.1f, 0.1f, 0.1f};

    EXPECT_COLOR_EQ(c1 + c2, {0.3f, 0.3f, 0.5f});

    static_assert(c1 + c2 == gleam::Color {0.3f, 0.3f, 0.5f});
}

TEST(Color, AdditionBlackColor) {
    constexpr auto c = gleam::Color {0.2f, 0.4f, 0.6f};
    constexpr auto black = gleam::Color {0x000000};

    EXPECT_COLOR_EQ(c + black, {0.2f, 0.4f, 0.6f});

    static_assert(c + black == gleam::Color {0.2f, 0.4f, 0.6f});
}

#pragma endregion

#pragma region Subtraction

TEST(Color, SubtractionBasic) {
    constexpr auto c1 = gleam::Color {0.2f, 0.8f, 0.4f};
    constexpr auto c2 = gleam::Color {0.2f, 0.4f, 0.1f};

    EXPECT_COLOR_EQ(c1 - c2, {0.0f, 0.4f, 0.3f});

    static_assert(c1 - c2 == gleam::Color {0.0f, 0.4f, 0.3f});
}

TEST(Color, SubtractionWithBlackColor) {
    constexpr auto c = gleam::Color {0.5f, 0.7f, 0.9f};
    constexpr auto black = gleam::Color {0x000000};

    EXPECT_COLOR_EQ(c - black, {0.5f, 0.7f, 0.9f});

    static_assert(c - black == gleam::Color {0.5f, 0.7f, 0.9f});
}

TEST(Color, SubtractionFromSelf) {
    constexpr auto c = gleam::Color {0.5f, 0.7f, 0.9f};

    EXPECT_COLOR_EQ(c - c, 0x000000);

    static_assert(c - c == gleam::Color {0x000000});
}

TEST(Color, SubtractionResultingInClamping) {
    constexpr auto c1 = gleam::Color {0.1f, 0.2f, 0.3f};
    constexpr auto c2 = gleam::Color {0.2f, 0.3f, 0.4f};
    constexpr auto result = c1 - c2;

    EXPECT_COLOR_EQ(result, {0.0f, 0.0f, 0.0f});

    static_assert(result == gleam::Color {0.0f, 0.0f, 0.0f});
}

#pragma endregion

#pragma region Multiplication

TEST(Color, ScalarMultiplication) {
    constexpr auto c = gleam::Color {0.2f, 0.4f, 0.6f} * 2.0f;

    EXPECT_COLOR_EQ(c, {0.4f, 0.8f, 1.2f});

    static_assert(c == gleam::Color {0.4f, 0.8f, 1.2f});
}


TEST(Color, ScalarMultiplicationInPlace) {
    auto c1 = gleam::Color {0.2f, 0.4f, 0.6f};
    c1 *= 2.0f;

    EXPECT_COLOR_EQ(c1, {0.4f, 0.8f, 1.2f});

    // Compile-time check
    constexpr auto c2 = []() {
        auto c = gleam::Color {0.2f, 0.4f, 0.6f};
        return c * 2.0f;
    }();

    static_assert(c2 == gleam::Color {0.4f, 0.8f, 1.2f});
}

#pragma endregion

#pragma region Lerp

TEST(Color, Lerp) {
    constexpr auto c1 = gleam::Color {0.0f, 0.0f, 0.0f};
    constexpr auto c2 = gleam::Color {1.0f, 1.0f, 1.0f};

    EXPECT_COLOR_EQ(gleam::Lerp(c1, c2, 0.5f), {0.5f, 0.5f, 0.5f});

    static_assert(gleam::Lerp(c1, c2, 0.5f) == gleam::Color {0.5f, 0.5f, 0.5f});
}

TEST(Color, LerpZeroFactor) {
    constexpr auto c1 = gleam::Color {0.5f, 0.5f, 0.5f};
    constexpr auto c2 = gleam::Color {1.0f, 1.0f, 1.0f};

    EXPECT_COLOR_EQ(gleam::Lerp(c1, c2, 0.0f), c1);

    static_assert(gleam::Lerp(c1, c2, 0.0f) == c1);
}

TEST(Color, LerpOneFactor) {
    constexpr auto c1 = gleam::Color {0.5f, 0.5f, 0.5f};
    constexpr auto c2 = gleam::Color {1.0f, 1.0f, 1.0f};

    EXPECT_COLOR_EQ(gleam::Lerp(c1, c2, 1.0f), c2);

    static_assert(gleam::Lerp(c1, c2, 1.0f) == c2);
}

#pragma endregion