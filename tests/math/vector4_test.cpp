// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <limits>

#include <gleam/math/vector4.hpp>
#include <gleam/math/vector3.hpp>

#pragma region Constructors

TEST(Vector4, ConstructorDefault) {
    const auto v = engine::Vector4 {};

    EXPECT_VEC4_EQ(v, {0.0f, 0.0f, 0.0f, 0.0f});
}

TEST(Vector4, ConstructorSingleParameter) {
    const auto v = engine::Vector4 {1.0f};

    EXPECT_VEC4_EQ(v, {1.0f, 1.0f, 1.0f, 1.0f});
}

TEST(Vector4, ConstructorParameterized) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0};

    EXPECT_VEC4_EQ(v, {1.0f, 2.0f, 3.0f, 4.0});
}

TEST(Vector4, ConstructWithVector3) {
    const auto v = engine::Vector4 {engine::Vector3(1.0f, 2.0f, 3.0f), 0.0f};

    EXPECT_VEC4_EQ(v, {1.0f, 2.0f, 3.0f, 0.0f});
}

#pragma endregion

#pragma region Component Access

TEST(Vector4, ComponentAccessDirect) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
    EXPECT_FLOAT_EQ(v.w, 4.0f);
}

TEST(Vector4, ComponentAccessRandomAccessOperator) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
    EXPECT_FLOAT_EQ(v[3], 4.0f);
    EXPECT_DEATH({ (void)v[4]; }, ".*i >= 0 && i < 4.*");
}

#pragma endregion

#pragma region Dot Product

TEST(Vector4, DotProductPositiveValues) {
    const auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    const auto v2 = engine::Vector4 {4.0f, 5.0f, 6.0f, 7.0f};

    EXPECT_FLOAT_EQ(engine::Dot(v1, v2), 60.0f);
}

TEST(Vector4, DotProductMixedValues) {
    const auto v1 = engine::Vector4 {-1.0f, 2.0f, -3.0f, 4.0f};
    const auto v2 = engine::Vector4 {4.0f, -5.0f, 6.0f, -7.0f};

    EXPECT_FLOAT_EQ(engine::Dot(v1, v2), -60.0f);
}

TEST(Vector4, DotProductZeroVector) {
    const auto v1 = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};
    const auto v2 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_FLOAT_EQ(engine::Dot(v1, v2), 0.0f);
}

TEST(Vector4, DotProductPerpendicularVectors) {
    const auto v1 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    const auto v2 = engine::Vector4 {0.0f, 1.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(engine::Dot(v1, v2), 0.0f);
}

TEST(Vector4, DotProductParallelVectors) {
    const auto v1 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    const auto v2 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(engine::Dot(v1, v2), 1.0f);
}

#pragma endregion

#pragma region Length

TEST(Vector4, LengthPositiveValues) {
    const auto v = engine::Vector4 {3.0f, 4.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 5.0f);
}

TEST(Vector4, LengthNegativeValues) {
    const auto v = engine::Vector4 {-3.0f, -4.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 5.0f);
}

TEST(Vector4, LengthZeroVector) {
    const auto v = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 0.0f);
}

TEST(Vector4, LengthUnitVector) {
    const auto v = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 1.0f);
}

TEST(Vector4, LengthSquaredPositiveValues) {
    const auto v = engine::Vector4 {3.0f, 4.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);
}

TEST(Vector4, LengthSquaredNegativeValues) {
    const auto v = engine::Vector4 {-3.0f, -4.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);
}

TEST(Vector4, LengthSquaredZeroVector) {
    const auto v = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 0.0f);
}

TEST(Vector4, LengthSquaredUnitVector) {
    const auto v = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 1.0f);
}

#pragma endregion

#pragma region Addition

TEST(Vector4, AdditionBasic) {
    const auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    const auto v2 = engine::Vector4 {5.0f, 6.0f, 7.0f, 8.0f};

    EXPECT_VEC4_EQ(v1 + v2, {6.0f, 8.0f, 10.0f, 12.0f});
}

TEST(Vector4, AdditionZeroVector) {
    const auto v1 = engine::Vector4 {9.0f, -1.0f, 2.0f, -4.0f};
    const auto v2 = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_VEC4_EQ(v1 + v2, {9.0f, -1.0f, 2.0f, -4.0f});
}

TEST(Vector4, AdditionNegativeValues) {
    const auto v1 = engine::Vector4 {-1.0f, -2.0f, -3.0f, -4.0f};
    const auto v2 = engine::Vector4 {-5.0f, -6.0f, -7.0f, -8.0f};

    EXPECT_VEC4_EQ(v1 + v2, {-6.0f, -8.0f, -10.0f, -12.0f});
}

TEST(Vector4, AdditionAssignment) {
    auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    v += engine::Vector4 {5.0f, 6.0f, 7.0f, 8.0f};

    EXPECT_VEC4_EQ(v, {6.0f, 8.0f, 10.0f, 12.0f});
}

#pragma endregion

#pragma region Subtraction

TEST(Vector4, SubtractionBasic) {
    const auto v1 = engine::Vector4 {10.0f, 9.0f, 8.0f, 7.0f};
    const auto v2 = engine::Vector4 {4.0f, 3.0f, 2.0f, 1.0f};

    EXPECT_VEC4_EQ(v1 - v2, {6.0f, 6.0f, 6.0f, 6.0f});
}

TEST(Vector4, SubtractionFromSelf) {
    const auto v = engine::Vector4 {3.0f, 5.0f, 7.0f, 9.0f};

    EXPECT_VEC4_EQ(v - v, {0.0f, 0.0f, 0.0f, 0.0f});
}

TEST(Vector4, SubtractionFromZeroVector) {
    const auto v1 = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};
    const auto v2 = engine::Vector4 {2.0f, 4.0f, 6.0f, 8.0f};

    EXPECT_VEC4_EQ(v1 - v2, {-2.0f, -4.0f, -6.0f, -8.0f});
}

TEST(Vector4, SubtractionAssignment) {
    auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    v -= engine::Vector4 {4.0f, 5.0f, 6.0f, 7.0f};

    EXPECT_VEC4_EQ(v, {-3.0f, -3.0f, -3.0f, -3.0f});
}

#pragma endregion

#pragma region Multiplication

TEST(Vector4, ScalarMultiplicationPositiveScalar) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_VEC4_EQ(v * 2.0f, {2.0f, 4.0f, 6.0f, 8.0f});
    EXPECT_VEC4_EQ(2.0f * v, {2.0f, 4.0f, 6.0f, 8.0f});
}

TEST(Vector4, ScalarMultiplicationNegativeScalar) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_VEC4_EQ(v * -1.0f, {-1.0f, -2.0f, -3.0f, -4.0f});
    EXPECT_VEC4_EQ(-1.0f * v, {-1.0f, -2.0f, -3.0f, -4.0f});
}

TEST(Vector4, ScalarMultiplicationZeroScalar) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_VEC4_EQ(v * 0.0f, {0.0f, 0.0f, 0.0f, 0.0f});
    EXPECT_VEC4_EQ(0.0f * v, {0.0f, 0.0f, 0.0f, 0.0f});
}

TEST(Vector4, ScalarMultiplicationIdentity) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_VEC4_EQ(v * 1.0f, {1.0f, 2.0f, 3.0f, 4.0f});
    EXPECT_VEC4_EQ(1.0f * v, {1.0f, 2.0f, 3.0f, 4.0f});
}

TEST(Vector4, ScalarMultiplicationAssignment) {
    auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    v *= 2.0f;

    EXPECT_VEC4_EQ(v, {2.0f, 4.0f, 6.0f, 8.0f});
}

TEST(Vector4, VectorMultiplicationAssignment) {
    auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    v1 *= engine::Vector4 {4.0f, 5.0f, 6.0f, 7.0f};

    EXPECT_VEC4_EQ(v1, {4.0f, 10.0f, 18.0f, 28.0f});
}

TEST(Vector4, VectorMultiplication) {
    const auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    const auto v2 = engine::Vector4 {4.0f, 5.0f, 6.0f, 7.0f};

    EXPECT_VEC4_EQ(v1 * v2, {4.0f, 10.0f, 18.0f, 28.0f});
}

#pragma endregion

#pragma region Division

TEST(Vector4, ScalarDivisionPositiveScalar) {
    const auto v = engine::Vector4 {2.0f, 4.0f, 6.0f, 8.0f};

    EXPECT_VEC4_EQ(v / 2.0f, {1.0f, 2.0f, 3.0f, 4.0f});
}

TEST(Vector4, ScalarDivisionNegativeScalar) {
    const auto v = engine::Vector4 {-2.0f, -4.0f, -6.0f, -8.0f};

    EXPECT_VEC4_EQ(v / -2.0f, {1.0f, 2.0f, 3.0f, 4.0f});
}

TEST(Vector4, ScalarDivisionZeroScalar) {
    const auto v = engine::Vector4 {2.0f, -4.0f, 6.0f, -8.0f};
    const auto inf = std::numeric_limits<float>::infinity();

    EXPECT_VEC4_EQ(v / 0.0f, {inf, -inf, inf, -inf});
}

TEST(Vector4, ScalarDivisionIdentity) {
    const auto v = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_VEC4_EQ(v / 1.0f, {1.0f, 2.0f, 3.0f, 4.0f});
}

#pragma endregion

#pragma region Normalize

TEST(Vector4, NormalizeBasic) {
    const auto v = engine::Vector4 {3.0f, 4.0f, 0.0f, 0.0f};

    EXPECT_VEC4_EQ(engine::Normalize(v), {0.6f, 0.8f, 0.0f, 0.0f});
}

TEST(Vector4, NormalizeNormalizedVector) {
    const auto v = engine::Vector4 {0.6f, 0.8f, 0.0f, 0.0f};

    EXPECT_VEC4_EQ(engine::Normalize(v), {0.6f, 0.8f, 0.0f, 0.0f});
}

TEST(Vector4, NormalizeZeroVector) {
    const auto v = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};

    EXPECT_VEC4_EQ(engine::Normalize(v), {0.0f, 0.0f, 0.0f, 0.0f});
}

TEST(Vector4, NormalizedMemberBasic) {
    auto v = engine::Vector4 {3.0f, 4.0f, 0.0f, 0.0f};
    v.Normalize();

    EXPECT_VEC4_EQ(v, {0.6f, 0.8f, 0.0f, 0.0f});
}

TEST(Vector4, NormalizedMemberNormalizedVector) {
    auto v = engine::Vector4 {0.6f, 0.8f, 0.0f, 0.0f};
    v.Normalize();

    EXPECT_VEC4_EQ(v, {0.6f, 0.8f, 0.0f, 0.0f});
}

TEST(Vector4, NormalizedMemberZeroVector) {
    auto v = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};
    v.Normalize();

    EXPECT_VEC4_EQ(v, {0.0f, 0.0f, 0.0f, 0.0f});
}

#pragma endregion

#pragma region Equality Operator

TEST(Vector4, EqualityOperator) {
    const auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 1.0f};
    const auto v2 = engine::Vector4 {1.0f, 2.0f, 3.0f, 1.0f};
    const auto v3 = engine::Vector4 {4.0f, 5.0f, 6.0f, 1.0f};

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vector4, InequalityOperator) {
    const auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 1.0f};
    const auto v2 = engine::Vector4 {1.0f, 2.0f, 3.0f, 1.0f};
    const auto v3 = engine::Vector4 {4.0f, 5.0f, 6.0f, 1.0f};

    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
}

#pragma endregion

#pragma region Lerp

TEST(Vector4, Lerp) {
    const auto v1 = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};
    const auto v2 = engine::Vector4 {1.0f, 1.0f, 1.0f, 1.0f};

    EXPECT_VEC4_EQ(engine::Lerp(v1, v2, 0.5f), {0.5f, 0.5f, 0.5f, 0.5f});
}

TEST(Vector4, LerpZeroFactor) {
    const auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    const auto v2 = engine::Vector4 {5.0f, 6.0f, 7.0f, 8.0f};

    EXPECT_VEC4_EQ(engine::Lerp(v1, v2, 0.0f), {1.0f, 2.0f, 3.0f, 4.0f});
}

TEST(Vector4, LerpOneFactor) {
    const auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    const auto v2 = engine::Vector4 {5.0f, 6.0f, 7.0f, 8.0f};

    EXPECT_VEC4_EQ(engine::Lerp(v1, v2, 1.0f), {5.0f, 6.0f, 7.0f, 8.0f});
}

#pragma endregion