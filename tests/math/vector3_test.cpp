/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <limits>

#include <gleam/math/vector3.hpp>

#pragma region Constructors

TEST(Vector3, ConstructorDefault) {
    const auto v = gleam::Vector3 {};

    EXPECT_VEC3_EQ(v, {0.0f, 0.0f, 0.0f});
}

TEST(Vector3, ConstructorSingleParameter) {
    const auto v = gleam::Vector3 {1.0f};

    EXPECT_VEC3_EQ(v, {1.0f, 1.0f, 1.0f});
}

TEST(Vector3, ConstructorParameterized) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(v, {1.0f, 2.0f, 3.0f});
}

#pragma endregion

#pragma region Unit vectors

TEST(Vector3, UnitVectorAlongX) {
    const auto v = gleam::Vector3::Right();

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vector3, UnitVectorAlongY) {
    const auto v = gleam::Vector3::Up();

    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vector3, UnitVectorAlongZ) {
    const auto v = gleam::Vector3::Forward();

    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 1.0f);
}

#pragma endregion

#pragma region Component Access

TEST(Vector3, ComponentAccessDirect) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(Vector3, ComponentAccessRandomAccessOperator) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
    EXPECT_DEATH({ (void)v[3]; }, ".*i >= 0 && i < 3.*");
}

#pragma endregion

#pragma region Cross Product

TEST(Vector3, CrossProductPositiveValues) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(gleam::Cross(v1, v2), {-3.0f, 6.0f, -3.0f});
}

TEST(Vector3, CrossProductZeroVector) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_VEC3_EQ(gleam::Cross(v1, v2), {0.0f, 0.0f, 0.0f});
}

TEST(Vector3, CrossProductParallelVectors) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {2.0f, 4.0f, 6.0f};

    EXPECT_VEC3_EQ(gleam::Cross(v1, v2), {0.0f, 0.0f, 0.0f});
}

TEST(Vector3, CrossProductUnitVectors) {
    const auto v1 = gleam::Vector3 {1.0f, 0.0f, 0.0f};
    const auto v2 = gleam::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_VEC3_EQ(gleam::Cross(v1, v2), {0.0f, 0.0f, 1.0f});
}

#pragma endregion

#pragma region Dot Product

TEST(Vector3, DotProductPositiveValues) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_FLOAT_EQ(gleam::Dot(v1, v2), 32.0f);
}

TEST(Vector3, DotProductMixedValues) {
    const auto v1 = gleam::Vector3 {-1.0f, 2.0f, -3.0f};
    const auto v2 = gleam::Vector3 {4.0f, -5.0f, 6.0f};

    EXPECT_FLOAT_EQ(gleam::Dot(v1, v2), -32.0f);
}

TEST(Vector3, DotProductZeroVector) {
    const auto v1 = gleam::Vector3 {0.0f, 0.0f, 0.0f};
    const auto v2 = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_FLOAT_EQ(gleam::Dot(v1, v2), 0.0f);
}

TEST(Vector3, DotProductPerpendicularVectors) {
    const auto v1 = gleam::Vector3 {1.0f, 0.0f, 0.0f};
    const auto v2 = gleam::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_FLOAT_EQ(gleam::Dot(v1, v2), 0.0f);
}

TEST(Vector3, DotProductParallelVectors) {
    const auto v1 = gleam::Vector3 {1.0f, 0.0f, 0.0f};
    const auto v2 = gleam::Vector3 {1.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(gleam::Dot(v1, v2), 1.0f);
}

#pragma endregion

#pragma region Length

TEST(Vector3, LengthPositiveValues) {
    const auto v = gleam::Vector3 {3.0f, 4.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 5.0f);
}

TEST(Vector3, LengthNegativeValues) {
    const auto v = gleam::Vector3 {-3.0f, -4.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 5.0f);
}

TEST(Vector3, LengthZeroVector) {
    const auto v = gleam::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 0.0f);
}

TEST(Vector3, LengthUnitVector) {
    const auto v = gleam::Vector3 {1.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.Length(), 1.0f);
}

TEST(Vector3, LengthSquarePositiveValues) {
    const auto v = gleam::Vector3 {3.0f, 4.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);
}

TEST(Vector3, LengthSquareNegativeValues) {
    const auto v = gleam::Vector3 {-3.0f, -4.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);
}

TEST(Vector3, LengthSquareZeroVector) {
    const auto v = gleam::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 0.0f);
}

TEST(Vector3, LengthSquareUnitVector) {
    const auto v = gleam::Vector3 {1.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(v.LengthSquared(), 1.0f);
}

#pragma endregion

#pragma region Addition

TEST(Vector3, AdditionBasic) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(v1 + v2, {5.0f, 7.0f, 9.0f});
}

TEST(Vector3, AdditionZeroVector) {
    const auto v1 = gleam::Vector3 {7.0f, -3.0f, 2.0f};
    const auto v2 = gleam::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_VEC3_EQ(v1 + v2, {7.0f, -3.0f, 2.0f});
}

TEST(Vector3, AdditionNegativeValues) {
    const auto v1 = gleam::Vector3 {-1.0f, -2.0f, -3.0f};
    const auto v2 = gleam::Vector3 {-4.0f, -5.0f, -6.0f};

    EXPECT_VEC3_EQ(v1 + v2, {-5.0f, -7.0f, -9.0f});
}

TEST(Vector3, AdditionAssignment) {
    auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    v += gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(v, {5.0f, 7.0f, 9.0f});
}

#pragma endregion

#pragma region Subtraction

TEST(Vector3, SubtractionBasic) {
    const auto v1 = gleam::Vector3 {5.0f, 6.0f, 7.0f};
    const auto v2 = gleam::Vector3 {3.0f, 2.0f, 1.0f};

    EXPECT_VEC3_EQ(v1 - v2, {2.0f, 4.0f, 6.0f});
}

TEST(Vector3, SubtractionFromSelf) {
    const auto v = gleam::Vector3 {9.0f, 8.0f, 7.0f};

    EXPECT_VEC3_EQ(v - v, {0.0f, 0.0f, 0.0f});
}

TEST(Vector3, SubtractionFromZeroVector) {
    const auto v1 = gleam::Vector3 {0.0f, 0.0f, 0.0f};
    const auto v2 = gleam::Vector3 {2.0f, 4.0f, 6.0f};

    EXPECT_VEC3_EQ(v1 - v2, {-2.0f, -4.0f, -6.0f});
}

TEST(Vector3, SubtractionAssignment) {
    auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    v -= gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(v, {-3.0f, -3.0f, -3.0f});
}

#pragma endregion

#pragma region Multiplication

TEST(Vector3, ScalarMultiplicationPositiveScalar) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(v * 2.0f, {2.0f, 4.0f, 6.0f});
    EXPECT_VEC3_EQ(2.0f * v, {2.0f, 4.0f, 6.0f});
}

TEST(Vector3, ScalarMultiplicationNegativeScalar) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(v * -1.0f, {-1.0f, -2.0f, -3.0f});
    EXPECT_VEC3_EQ(-1.0f * v, {-1.0f, -2.0f, -3.0f});
}

TEST(Vector3, ScalarMultiplicationZeroScalar) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(v * 0.0f, {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(0.0f * v, {0.0f, 0.0f, 0.0f});
}

TEST(Vector3, ScalarMultiplicationIdentity) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(v * 1.0f, {1.0f, 2.0f, 3.0f});
    EXPECT_VEC3_EQ(1.0f * v, {1.0f, 2.0f, 3.0f});
}

TEST(Vector3, ScalarMultiplicationAssignment) {
    auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    v *= 2.0f;

    EXPECT_VEC3_EQ(v, {2.0f, 4.0f, 6.0f});
}

TEST(Vector3, VectorMultiplication) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(v1 * v2, {4.0f, 10.0f, 18.0f});
}

TEST(Vector3, VectorMultiplicationAssignment) {
    auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    v1 *= gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(v1, {4.0f, 10.0f, 18.0f});
}

#pragma endregion

#pragma region Division

TEST(Vector3, ScalarDivisionPositiveScalar) {
    const auto v = gleam::Vector3 {2.0f, 4.0f, 6.0f};

    EXPECT_VEC3_EQ(v / 2.0f, {1.0f, 2.0f, 3.0f});
}

TEST(Vector3, ScalarDivisionNegativeScalar) {
    const auto v = gleam::Vector3 {-2.0f, -4.0f, -6.0f};

    EXPECT_VEC3_EQ(v / -2.0f, {1.0f, 2.0f, 3.0f});
}

TEST(Vector3, ScalarDivisionZeroScalar) {
    const auto v = gleam::Vector3 {2.0f, -4.0f, 6.0f};
    const auto inf = std::numeric_limits<float>::infinity();

    EXPECT_VEC3_EQ(v / 0.0f, {inf, -inf, inf});
}

TEST(Vector3, ScalarDivisionIdentity) {
    const auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(v / 1.0f, {1.0f, 2.0f, 3.0f});
}

#pragma endregion

#pragma region Normalize

TEST(Vector3, NormalizeBasic) {
    const auto v = gleam::Vector3 {3.0f, 4.0f, 0.0f};

    EXPECT_VEC3_EQ(gleam::Normalize(v), {0.6f, 0.8f, 0.0f});
}

TEST(Vector3, NormalizeNormalizedVector) {
    const auto v = gleam::Vector3 {0.6f, 0.8f, 0.0f};

    EXPECT_VEC3_EQ(gleam::Normalize(v), {0.6f, 0.8f, 0.0f});
}

TEST(Vector3, NormalizeZeroVector) {
    const auto v = gleam::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_VEC3_EQ(gleam::Normalize(v), {0.0f, 0.0f, 0.0f});
}

TEST(Vector3, NormalizeMemberBasic) {
    auto v = gleam::Vector3 {3.0f, 4.0f, 0.0f};
    v.Normalize();

    EXPECT_VEC3_EQ(v, {0.6f, 0.8f, 0.0f});
}

TEST(Vector3, NormalizeMemberNormalizedVector) {
    auto v = gleam::Vector3 {0.6f, 0.8f, 0.0f};
    v.Normalize();

    EXPECT_VEC3_EQ(v, {0.6f, 0.8f, 0.0f});
}

TEST(Vector3, NormalizedMemberZeroVector) {
    auto v = gleam::Vector3 {0.0f, 0.0f, 0.0f};
    v.Normalize();

    EXPECT_VEC3_EQ(v, {0.0f, 0.0f, 0.0f});
}

#pragma endregion

#pragma region Equality Operator

TEST(Vector3, EqualityOperator) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v3 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vector3, InequalityOperator) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v3 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
}

#pragma endregion

#pragma region Lerp

TEST(Vector3, Lerp) {
    const auto v1 = gleam::Vector3 {0.0f, 0.0f, 0.0f};
    const auto v2 = gleam::Vector3 {1.0f, 1.0f, 1.0f};

    EXPECT_VEC3_EQ(gleam::Lerp(v1, v2, 0.5f), {0.5f, 0.5f, 0.5f});
}

TEST(Vector3, LerpZeroFactor) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(gleam::Lerp(v1, v2, 0.0f), {1.0f, 2.0f, 3.0f});
}

TEST(Vector3, LerpOneFactor) {
    const auto v1 = gleam::Vector3 {1.0f, 2.0f, 3.0f};
    const auto v2 = gleam::Vector3 {4.0f, 5.0f, 6.0f};

    EXPECT_VEC3_EQ(gleam::Lerp(v1, v2, 1.0f), {4.0f, 5.0f, 6.0f});
}

#pragma endregion