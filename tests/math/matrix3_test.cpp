// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix3.hpp>

#pragma region Constructors

TEST(Matrix3, ConstructorDefault) {
    const auto m = engine::Matrix3 {};

    EXPECT_MAT3_EQ(m, {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    });
}

TEST(Matrix3, ConstructorSingleParameter) {
    const auto m = engine::Matrix3 {1.0f};

    EXPECT_MAT3_EQ(m, {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Matrix3, ConstructorParameterized) {
    const auto m = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    EXPECT_MAT3_EQ(m, {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });
}

TEST(Matrix3, ConstructorVector) {
    const auto m = engine::Matrix3 {
        engine::Vector3 {1.0f, 4.0f, 7.0f},
        engine::Vector3 {2.0f, 5.0f, 8.0f},
        engine::Vector3 {3.0f, 6.0f, 9.0f},
    };

    EXPECT_MAT3_EQ(m, {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });
}

#pragma endregion

#pragma region Matrix Multiplication

TEST(Matrix3, MultiplicationMatrix) {
    const auto m1 = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    const auto m2 = engine::Matrix3 {
        1.0f, 5.0f, 1.0f,
        2.0f, 1.0f, 3.0f,
        1.0f, 5.0f, 4.0f
    };

    EXPECT_MAT3_EQ((m1 * m2), {
         8.0f, 22.0f, 19.0f,
        24.0f, 66.0f, 51.0f,
        12.0f, 33.0f, 21.0f,
    });
}

#pragma region Equality Operator

TEST(Matrix3, EqualityOperator) {
    const auto m1 = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    const auto m2 = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    const auto m3 = engine::Matrix3 {
        1.0f, 5.0f, 1.0f,
        2.0f, 1.0f, 3.0f,
        1.0f, 5.0f, 4.0f
    };

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
}

TEST(Matrix3, InequalityOperator) {
    const auto m1 = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    const auto m2 = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    const auto m3 = engine::Matrix3 {
        1.0f, 5.0f, 1.0f,
        2.0f, 1.0f, 3.0f,
        1.0f, 5.0f, 4.0f
    };

    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);
}

#pragma endregion

#pragma region Operators

TEST(Matrix3, SubscriptOperatorReturnsColumnVector) {
    const auto m = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };

    EXPECT_VEC3_EQ(m[0], {1.0f, 5.0f, 4.0f});
    EXPECT_VEC3_EQ(m[1], {2.0f, 6.0f, 3.0f});
    EXPECT_VEC3_EQ(m[2], {3.0f, 7.0f, 2.0f});
}

TEST(Matrix3, CallOperatorReturnsElementsRowMajor) {
    const auto m = engine::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };

    EXPECT_EQ(m(0, 0), 1.0f);
    EXPECT_EQ(m(0, 1), 2.0f);
    EXPECT_EQ(m(0, 2), 3.0f);

    EXPECT_EQ(m(1, 0), 5.0f);
    EXPECT_EQ(m(1, 1), 6.0f);
    EXPECT_EQ(m(1, 2), 7.0f);

    EXPECT_EQ(m(2, 0), 4.0f);
    EXPECT_EQ(m(2, 1), 3.0f);
    EXPECT_EQ(m(2, 2), 2.0f);
}

#pragma endregion