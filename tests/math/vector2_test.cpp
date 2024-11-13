// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/vector2.hpp>

#pragma region Constructors

TEST(Vector2, ConstructorDefault) {
    const auto v = engine::Vector2 {};

    EXPECT_VEC2_EQ(v, {0.0f, 0.0f});
}

TEST(Vector2, ConstructorSingleParameter) {
    const auto v = engine::Vector2 {1.0f};

    EXPECT_VEC2_EQ(v, {1.0f, 1.0f});
}

TEST(Vector2, ConstructorParameterized) {
    const auto v = engine::Vector2 {1.0f, 2.0f};

    EXPECT_VEC2_EQ(v, {1.0f, 2.0f});
}

#pragma endregion

#pragma region Subtraction

TEST(Vector2, SubtractionBasic) {
    const auto v1 = engine::Vector2 {5.0f, 6.0f};
    const auto v2 = engine::Vector2 {3.0f, 2.0f};

    EXPECT_VEC2_EQ(v1 - v2, {2.0f, 4.0f});
}

TEST(Vector2, SubtractionFromSelf) {
    const auto v = engine::Vector2 {9.0f, 8.0f};

    EXPECT_VEC2_EQ(v - v, {0.0f, 0.0f});
}

TEST(Vector2, SubtractionFromZeroVector) {
    const auto v1 = engine::Vector2 {0.0f, 0.0f};
    const auto v2 = engine::Vector2 {2.0f, 4.0f};

    EXPECT_VEC2_EQ(v1 - v2, {-2.0f, -4.0f});
}

#pragma endregion

#pragma region Equality Operator

TEST(Vector2, EqualityOperator) {
    const auto v1 = engine::Vector2 {1.0f, 2.0f};
    const auto v2 = engine::Vector2 {1.0f, 2.0f};
    const auto v3 = engine::Vector2 {4.0f, 5.0f};

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vector2, InequalityOperator) {
    const auto v1 = engine::Vector2 {1.0f, 2.0f};
    const auto v2 = engine::Vector2 {1.0f, 2.0f};
    const auto v3 = engine::Vector2 {4.0f, 5.0f};

    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
}

#pragma endregion