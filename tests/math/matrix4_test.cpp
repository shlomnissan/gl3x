/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gl3x/math/matrix4.hpp>

#include <cassert>

#pragma region Constructors

TEST(Matrix4, ConstructorDefault) {
    constexpr auto m = gl3x::Matrix4 {};

    EXPECT_MAT4_EQ(m, {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    });

    static_assert(m == gl3x::Matrix4 {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    });
}

TEST(Matrix4, ConstructorSingleParameter) {
    constexpr auto m = gl3x::Matrix4 {1.0f};

    EXPECT_MAT4_EQ(m, {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    static_assert(m == gl3x::Matrix4 {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Matrix4, ConstructorParameterized) {
    constexpr auto m = gl3x::Matrix4 {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    EXPECT_MAT4_EQ(m, {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    });

    static_assert(m == gl3x::Matrix4 {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    });
}

TEST(Matrix4, ConstructorVector) {
    constexpr auto m = gl3x::Matrix4 {
        gl3x::Vector4 {1.0f, 5.0f,  9.0f, 13.0f},
        gl3x::Vector4 {2.0f, 6.0f, 10.0f, 14.0f},
        gl3x::Vector4 {3.0f, 7.0f, 11.0f, 15.0f},
        gl3x::Vector4 {4.0f, 8.0f, 12.0f, 16.0f}
    };

    EXPECT_MAT4_EQ(m, {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    });

    static_assert(m == gl3x::Matrix4 {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    });
}

#pragma endregion

#pragma region Matrix Multiplication

TEST(Matrix4, MultiplicationMatrix) {
    constexpr auto m1 = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };
    constexpr auto m2 = gl3x::Matrix4 {
        1.0f, 5.0f, 1.0f, 8.0f,
        2.0f, 1.0f, 3.0f, 1.0f,
        1.0f, 5.0f, 4.0f, 2.0f,
        9.0f, 6.0f, 1.0f, 3.0f
    };

    EXPECT_MAT4_EQ((m1 * m2), {
        44.0f,  46.0f, 23.0f, 28.0f,
        96.0f, 114.0f, 59.0f, 84.0f,
        21.0f,  39.0f, 22.0f, 42.0f,
        73.0f, 107.0f, 58.0f, 98.0f
    });

    static_assert(m1 * m2 == gl3x::Matrix4 {
        44.0f,  46.0f, 23.0f, 28.0f,
        96.0f, 114.0f, 59.0f, 84.0f,
        21.0f,  39.0f, 22.0f, 42.0f,
        73.0f, 107.0f, 58.0f, 98.0f
    });
}

#pragma endregion

#pragma region Matrix-Vector Multiplication

TEST(Matrix4, MultiplicationWithVector4) {
    constexpr auto m = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };
    constexpr auto v = gl3x::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_VEC4_EQ(m * v, {30.0f, 70.0f, 20.0f, 60.0f});

    static_assert(m * v == gl3x::Vector4 {30.0f, 70.0f, 20.0f, 60.0f});
}

TEST(Matrix4, MultiplicationWithVector3) {
    constexpr auto m = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };
    constexpr auto v = gl3x::Vector3 {1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ(m * v, {18.0f, 46.0f, 17.0f});

    static_assert(m * v == gl3x::Vector3 {18.0f, 46.0f, 17.0f});
}

#pragma endregion

#pragma region Equality Operator

TEST(Matrix4, EqualityOperator) {
    constexpr auto m1 = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };
    constexpr auto m2 = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };
    constexpr auto m3 = gl3x::Matrix4 {
        1.0f, 5.0f, 1.0f, 8.0f,
        2.0f, 1.0f, 3.0f, 1.0f,
        1.0f, 5.0f, 4.0f, 2.0f,
        9.0f, 6.0f, 1.0f, 3.0f
    };

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);

    static_assert(m1 == m2);
    static_assert(m1 != m3);
}

TEST(Matrix4, InequalityOperator) {
    constexpr auto m1 = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };
    constexpr auto m2 = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };
    constexpr auto m3 = gl3x::Matrix4 {
        1.0f, 5.0f, 1.0f, 8.0f,
        2.0f, 1.0f, 3.0f, 1.0f,
        1.0f, 5.0f, 4.0f, 2.0f,
        9.0f, 6.0f, 1.0f, 3.0f
    };

    EXPECT_FALSE(m1 != m2);
    EXPECT_TRUE(m1 != m3);

    static_assert(m1 == m2);
    static_assert(m1 != m3);
}

#pragma endregion

#pragma region Determinant

TEST(Matrix4, Determinant) {
    constexpr auto m = gl3x::Matrix4 {
        4.0f, 7.0f, 2.0f, 1.0f,
        3.0f, 6.0f, 1.0f, 2.0f,
        2.0f, 5.0f, 3.0f, 3.0f,
        1.0f, 1.0f, 2.0f, 1.0f
    };

    EXPECT_FLOAT_EQ(gl3x::Determinant(m), 18.0f);

    static_assert(gl3x::Determinant(m) == 18.0f);
}

TEST(Matrix4, DeterminantNegative) {
    constexpr auto m = gl3x::Matrix4 {
        2.0f, 4.0f, 1.0f, 3.0f,
        5.0f, 6.0f, 2.0f, 1.0f,
        3.0f, 1.0f, 4.0f, 2.0f,
        7.0f, 8.0f, 5.0f, 6.0f
    };

    EXPECT_FLOAT_EQ(gl3x::Determinant(m), -30.0f);

    static_assert(gl3x::Determinant(m) == -30.0f);
}

TEST(Matrix4, DeterminantZero) {
    constexpr auto m = gl3x::Matrix4 {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    EXPECT_FLOAT_EQ(gl3x::Determinant(m), 0.0f);

    static_assert(gl3x::Determinant(m) == 0.0f);
}

#pragma endregion

#pragma region Inverse

TEST(Matrix4, Inverse) {
    constexpr auto m = gl3x::Matrix4 {
        4.0f, 7.0f, 2.0f, 1.0f,
        3.0f, 6.0f, 1.0f, 2.0f,
        2.0f, 5.0f, 3.0f, 3.0f,
        1.0f, 1.0f, 2.0f, 1.0f
    };

    constexpr auto inverse = gl3x::Inverse(m);
    EXPECT_MAT4_NEAR(inverse, {
       -0.33f,  1.00f, -1.00f,  1.33f,
        0.33f, -0.50f,  0.50f, -0.83f,
        0.33f, -0.66f,  0.33f,  0.00f,
       -0.66f,  0.83f, -0.16f,  0.50f
    }, 0.01f);

    // M^{-1} * M = I
    EXPECT_MAT4_NEAR(
        inverse * m,
        gl3x::Matrix4::Identity(),
        0.01f
    );

    static_assert(ApproxEqual(inverse(0, 0), -0.33f, 1e-2f));
    static_assert(ApproxEqual(inverse(0, 1), 1.00f, 1e-2f));
    static_assert(ApproxEqual(inverse(0, 2), -1.00f, 1e-2f));
    static_assert(ApproxEqual(inverse(0, 3), 1.33f, 1e-2f));
    static_assert(ApproxEqual(inverse(1, 0), 0.33f, 1e-2f));
    static_assert(ApproxEqual(inverse(1, 1), -0.50f, 1e-2f));
    static_assert(ApproxEqual(inverse(1, 2), 0.50f, 1e-2f));
    static_assert(ApproxEqual(inverse(1, 3), -0.83f, 1e-2f));
    static_assert(ApproxEqual(inverse(2, 0), 0.33f, 1e-2f));
    static_assert(ApproxEqual(inverse(2, 1), -0.66f, 1e-2f));
    static_assert(ApproxEqual(inverse(2, 2), 0.33f, 1e-2f));
    static_assert(ApproxEqual(inverse(2, 3), 0.0f, 1e-2f));
    static_assert(ApproxEqual(inverse(3, 0), -0.66f, 1e-2f));
    static_assert(ApproxEqual(inverse(3, 1), 0.83f, 1e-2f));
    static_assert(ApproxEqual(inverse(3, 2), -0.16f, 1e-2f));
    static_assert(ApproxEqual(inverse(3, 3), 0.50f, 1e-2f));
}

#pragma endregion

#pragma region Transpose

TEST(Matrix4, TransposeIdentity) {
    constexpr auto m = gl3x::Matrix4::Identity();

    EXPECT_MAT4_EQ(gl3x::Transpose(m), {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    static_assert(gl3x::Transpose(m) == gl3x::Matrix4 {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Matrix4, TransposeNonIdentity) {
    constexpr auto m = gl3x::Matrix4 {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
       13.0f, 14.0f, 15.0f, 16.0f
    };

    EXPECT_MAT4_EQ(gl3x::Transpose(m), {
        1.0f,  5.0f,  9.0f, 13.0f,
        2.0f,  6.0f, 10.0f, 14.0f,
        3.0f,  7.0f, 11.0f, 15.0f,
        4.0f,  8.0f, 12.0f, 16.0f
    });

    static_assert(gl3x::Transpose(m) == gl3x::Matrix4 {
        1.0f,  5.0f,  9.0f, 13.0f,
        2.0f,  6.0f, 10.0f, 14.0f,
        3.0f,  7.0f, 11.0f, 15.0f,
        4.0f,  8.0f, 12.0f, 16.0f
    });
}

#pragma endregion

#pragma region Operators

TEST(Matrix4, SubscriptOperatorReturnsColumnVectorConst) {
    constexpr auto m = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };

    EXPECT_VEC4_EQ(m[0], {1.0f, 5.0f, 4.0f, 8.0f});
    EXPECT_VEC4_EQ(m[1], {2.0f, 6.0f, 3.0f, 7.0f});
    EXPECT_VEC4_EQ(m[2], {3.0f, 7.0f, 2.0f, 6.0f});
    EXPECT_VEC4_EQ(m[3], {4.0f, 8.0f, 1.0f, 5.0f});

    static_assert(m[0] == gl3x::Vector4 {1.0f, 5.0f, 4.0f, 8.0f});
    static_assert(m[1] == gl3x::Vector4 {2.0f, 6.0f, 3.0f, 7.0f});
    static_assert(m[2] == gl3x::Vector4 {3.0f, 7.0f, 2.0f, 6.0f});
    static_assert(m[3] == gl3x::Vector4 {4.0f, 8.0f, 1.0f, 5.0f});
}

TEST(Matrix4, SubscriptOperatorReturnsColumnVectorReference) {
    auto m1 = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };

    auto& c1 = m1[0];
    auto& c2 = m1[1];
    auto& c3 = m1[2];
    auto& c4 = m1[3];

    c1.x *= 2.0f;
    c2.y *= 2.0f;
    c3.z *= 2.0f;
    c4.w *= 2.0f;

    EXPECT_MAT4_EQ(m1, {
        2.0f,  2.0f, 3.0f,  4.0f,
        5.0f, 12.0f, 7.0f,  8.0f,
        4.0f,  3.0f, 4.0f,  1.0f,
        8.0f,  7.0f, 6.0f, 10.0f,
    });

    // Compile-time check
    constexpr auto m2 = []() {
        auto m = gl3x::Matrix4 {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            4.0f, 3.0f, 2.0f, 1.0f,
            8.0f, 7.0f, 6.0f, 5.0f,
        };

        auto& c1 = m[0];
        auto& c2 = m[1];
        auto& c3 = m[2];
        auto& c4 = m[3];

        c1.x *= 2.0f;
        c2.y *= 2.0f;
        c3.z *= 2.0f;
        c4.w *= 2.0f;

        return m;
    }();

    static_assert(m2 == gl3x::Matrix4 {
        2.0f,  2.0f, 3.0f,  4.0f,
        5.0f, 12.0f, 7.0f,  8.0f,
        4.0f,  3.0f, 4.0f,  1.0f,
        8.0f,  7.0f, 6.0f, 10.0f,
    });
}

TEST(Matrix4, CallOperatorReturnsElementsRowMajor) {
    constexpr auto m = gl3x::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 5.0f,
    };

    EXPECT_EQ(m(0, 0), 1.0f);  static_assert(m(0, 0) == 1.0f);
    EXPECT_EQ(m(0, 1), 2.0f);  static_assert(m(0, 1) == 2.0f);
    EXPECT_EQ(m(0, 2), 3.0f);  static_assert(m(0, 2) == 3.0f);
    EXPECT_EQ(m(0, 3), 4.0f);  static_assert(m(0, 3) == 4.0f);

    EXPECT_EQ(m(1, 0), 5.0f); static_assert(m(1, 0) == 5.0f);
    EXPECT_EQ(m(1, 1), 6.0f); static_assert(m(1, 1) == 6.0f);
    EXPECT_EQ(m(1, 2), 7.0f); static_assert(m(1, 2) == 7.0f);
    EXPECT_EQ(m(1, 3), 8.0f); static_assert(m(1, 3) == 8.0f);

    EXPECT_EQ(m(2, 0), 4.0f); static_assert(m(2, 0) == 4.0f);
    EXPECT_EQ(m(2, 1), 3.0f); static_assert(m(2, 1) == 3.0f);
    EXPECT_EQ(m(2, 2), 2.0f); static_assert(m(2, 2) == 2.0f);
    EXPECT_EQ(m(2, 3), 1.0f); static_assert(m(2, 3) == 1.0f);

    EXPECT_EQ(m(3, 0), 8.0f); static_assert(m(3, 0) == 8.0f);
    EXPECT_EQ(m(3, 1), 7.0f); static_assert(m(3, 1) == 7.0f);
    EXPECT_EQ(m(3, 2), 6.0f); static_assert(m(3, 2) == 6.0f);
    EXPECT_EQ(m(3, 3), 5.0f); static_assert(m(3, 3) == 5.0f);
}

#pragma endregion