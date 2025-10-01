/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gleam/math/matrix3.hpp>
#include <gleam/math/matrix4.hpp>

#include <cassert>

#pragma region Constructors

TEST(Matrix3, ConstructorDefault) {
    constexpr auto m = gleam::Matrix3 {};

    EXPECT_MAT3_EQ(m, {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    });

    static_assert(m == gleam::Matrix3 {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    });
}

TEST(Matrix3, ConstructorSingleParameter) {
    constexpr auto m = gleam::Matrix3 {1.0f};

    EXPECT_MAT3_EQ(m, {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });

    static_assert(m == gleam::Matrix3 {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Matrix3, ConstructorParameterized) {
    constexpr auto m = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    EXPECT_MAT3_EQ(m, {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });

    static_assert(m == gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });
}

TEST(Matrix3, ConstructorVector) {
    constexpr auto m = gleam::Matrix3 {
        gleam::Vector3 {1.0f, 4.0f, 7.0f},
        gleam::Vector3 {2.0f, 5.0f, 8.0f},
        gleam::Vector3 {3.0f, 6.0f, 9.0f},
    };

    EXPECT_MAT3_EQ(m, {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });

    static_assert(m == gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    });
}

TEST(Matrix3, ConstructorMatrix4) {
    constexpr auto m = gleam::Matrix3 {
        gleam::Matrix4 {
            1.0f,  2.0f,  3.0f,  4.0f,
            5.0f,  6.0f,  7.0f,  8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
           13.0f, 14.0f, 15.0f, 16.0f
        }
    };

    EXPECT_MAT3_EQ(m, {
        1.0f,  2.0f,  3.0f,
        5.0f,  6.0f,  7.0f,
        9.0f, 10.0f, 11.0f
    });

    static_assert(m == gleam::Matrix3 {
        1.0f,  2.0f,  3.0f,
        5.0f,  6.0f,  7.0f,
        9.0f, 10.0f, 11.0f
    });
}

#pragma endregion

#pragma region Matrix Multiplication

TEST(Matrix3, MultiplicationMatrix) {
    constexpr auto m1 = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    constexpr auto m2 = gleam::Matrix3 {
        1.0f, 5.0f, 1.0f,
        2.0f, 1.0f, 3.0f,
        1.0f, 5.0f, 4.0f
    };

    EXPECT_MAT3_EQ(m1 * m2, {
         8.0f, 22.0f, 19.0f,
        24.0f, 66.0f, 51.0f,
        12.0f, 33.0f, 21.0f,
    });

    static_assert(m1 * m2 == gleam::Matrix3 {
        8.0f, 22.0f, 19.0f,
        24.0f, 66.0f, 51.0f,
        12.0f, 33.0f, 21.0f,
    });
}

#pragma endregion

#pragma region Matrix-Vector Multiplication

TEST(Matrix3, MultiplicationWithVector3) {
    constexpr auto m = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    constexpr auto v = gleam::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(m * v, {14.0f, 38.0f, 16.0f});

    static_assert(m * v == gleam::Vector3 {14.0f, 38.0f, 16.0f});
}

#pragma endregion

#pragma region Equality Operator

TEST(Matrix3, EqualityOperator) {
    constexpr auto m1 = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    constexpr auto m2 = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    constexpr auto m3 = gleam::Matrix3 {
        1.0f, 5.0f, 1.0f,
        2.0f, 1.0f, 3.0f,
        1.0f, 5.0f, 4.0f
    };

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);

    static_assert(m1 == m2);
    static_assert(m1 != m3);
}

TEST(Matrix3, InequalityOperator) {
    constexpr auto m1 = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    constexpr auto m2 = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };
    constexpr auto m3 = gleam::Matrix3 {
        1.0f, 5.0f, 1.0f,
        2.0f, 1.0f, 3.0f,
        1.0f, 5.0f, 4.0f
    };

    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);

    static_assert(m1 == m2);
    static_assert(m1 != m3);
}

#pragma endregion

#pragma region Determinant

TEST(Matrix3, Determinant) {
    constexpr auto m = gleam::Matrix3 {
        4.0f, 7.0f, 2.0f,
        3.0f, 6.0f, 1.0f,
        2.0f, 5.0f, 3.0f
    };

    EXPECT_FLOAT_EQ(gleam::Determinant(m), 9.0f);
    // det(m) = volume of parallelepiped
    EXPECT_FLOAT_EQ(
        gleam::Determinant(m),
        gleam::Dot(gleam::Cross(m[0], m[1]), m[2])
    );

    static_assert(gleam::Determinant(m) == 9.0f);
}

TEST(Matrix3, DeterminantNegative) {
    constexpr auto m = gleam::Matrix3 {
        1.0f, 2.0f, 1.0f,
        3.0f, 1.0f, 1.0f,
        2.0f, 2.0f, 3.0f
    };

    EXPECT_FLOAT_EQ(gleam::Determinant(m), -9.0f);

    static_assert(gleam::Determinant(m) == -9.0f);
}

TEST(Matrix3, DeterminantZero) {
    constexpr auto m = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    EXPECT_FLOAT_EQ(gleam::Determinant(m), 0.0f);

    static_assert(gleam::Determinant(m) == 0.0f);
}

#pragma endregion

#pragma region Inverse

TEST(Matrix3, Inverse) {
    constexpr auto m = gleam::Matrix3 {
        4.0f, 7.0f, 2.0f,
        3.0f, 6.0f, 1.0f,
        2.0f, 5.0f, 3.0f
    };

    constexpr auto inverse = gleam::Inverse(m);
    EXPECT_MAT3_NEAR(inverse, {
        1.44f, -1.22f, -0.55f,
       -0.77f,  0.88f,  0.22f,
        0.33f, -0.66f,  0.33f
    }, 0.01f);

    // M^{-1} * M = I
    EXPECT_MAT3_NEAR(
        inverse * m,
        gleam::Matrix3::Identity(),
        0.01f
    );

    static_assert(ApproxEqual(inverse(0, 0), 1.44f, 1e-2f));
    static_assert(ApproxEqual(inverse(0, 1), -1.22f, 1e-2f));
    static_assert(ApproxEqual(inverse(0, 2), -0.55f, 1e-2f));
    static_assert(ApproxEqual(inverse(1, 0), -0.77f, 1e-2f));
    static_assert(ApproxEqual(inverse(1, 1), 0.88f, 1e-2f));
    static_assert(ApproxEqual(inverse(1, 2), 0.22f, 1e-2f));
    static_assert(ApproxEqual(inverse(2, 0), 0.33f, 1e-2f));
    static_assert(ApproxEqual(inverse(2, 1), -0.66f, 1e-2f));
    static_assert(ApproxEqual(inverse(2, 2), 0.33f, 1e-2f));
}

#pragma endregion

#pragma region Transpose

TEST(Matrix3, TransposeIdentity) {
    constexpr auto m = gleam::Matrix3::Identity();

    EXPECT_MAT3_EQ(gleam::Transpose(m), {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });

    static_assert(gleam::Transpose(m) == gleam::Matrix3 {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Matrix3, TransposeNonIdentity) {
    constexpr auto m = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    EXPECT_MAT3_EQ(gleam::Transpose(m), {
        1.0f, 4.0f, 7.0f,
        2.0f, 5.0f, 8.0f,
        3.0f, 6.0f, 9.0f
    });

    static_assert(gleam::Transpose(m) == gleam::Matrix3 {
        1.0f, 4.0f, 7.0f,
        2.0f, 5.0f, 8.0f,
        3.0f, 6.0f, 9.0f
    });
}

#pragma endregion

#pragma region Operators

TEST(Matrix3, SubscriptOperatorReturnsColumnVectorConst) {
    constexpr auto m = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };

    EXPECT_VEC3_EQ(m[0], {1.0f, 5.0f, 4.0f});
    EXPECT_VEC3_EQ(m[1], {2.0f, 6.0f, 3.0f});
    EXPECT_VEC3_EQ(m[2], {3.0f, 7.0f, 2.0f});

    static_assert(m[0] == gleam::Vector3 {1.0f, 5.0f, 4.0f});
    static_assert(m[1] == gleam::Vector3 {2.0f, 6.0f, 3.0f});
    static_assert(m[2] == gleam::Vector3 {3.0f, 7.0f, 2.0f});
}

TEST(Matrix3, SubscriptOperatorReturnsColumnVectorReference) {
    auto m1 = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };

    auto& c1 = m1[0];
    auto& c2 = m1[1];
    auto& c3 = m1[2];

    c1.x *= 2.0f;
    c2.y *= 2.0f;
    c3.z *= 2.0f;

    EXPECT_MAT3_EQ(m1, {
        2.0f,  2.0f, 3.0f,
        5.0f, 12.0f, 7.0f,
        4.0f,  3.0f, 4.0f
    });

    // Compile-time check
    constexpr auto m2 = []() {
        auto m = gleam::Matrix3 {
            1.0f, 2.0f, 3.0f,
            5.0f, 6.0f, 7.0f,
            4.0f, 3.0f, 2.0f
        };

        auto& c1 = m[0];
        auto& c2 = m[1];
        auto& c3 = m[2];

        c1.x *= 2.0f;
        c2.y *= 2.0f;
        c3.z *= 2.0f;

        return m;
    }();

    static_assert(m2 == gleam::Matrix3 {
        2.0f,  2.0f, 3.0f,
        5.0f, 12.0f, 7.0f,
        4.0f,  3.0f, 4.0f
    });
}

TEST(Matrix3, CallOperatorReturnsElementsRowMajor) {
    constexpr auto m = gleam::Matrix3 {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        4.0f, 3.0f, 2.0f
    };

    EXPECT_EQ(m(0, 0), 1.0f); static_assert(m(0, 0) == 1.0f);
    EXPECT_EQ(m(0, 1), 2.0f); static_assert(m(0, 1) == 2.0f);
    EXPECT_EQ(m(0, 2), 3.0f); static_assert(m(0, 2) == 3.0f);

    EXPECT_EQ(m(1, 0), 5.0f); static_assert(m(1, 0) == 5.0f);
    EXPECT_EQ(m(1, 1), 6.0f); static_assert(m(1, 1) == 6.0f);
    EXPECT_EQ(m(1, 2), 7.0f); static_assert(m(1, 2) == 7.0f);

    EXPECT_EQ(m(2, 0), 4.0f); static_assert(m(2, 0) == 4.0f);
    EXPECT_EQ(m(2, 1), 3.0f); static_assert(m(2, 1) == 3.0f);
    EXPECT_EQ(m(2, 2), 2.0f); static_assert(m(2, 2) == 2.0f);
}

#pragma endregion