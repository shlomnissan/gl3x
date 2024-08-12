// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/vector3.hpp>

#include <limits>

TEST(Vector3, Constructors) {
    // default constructor
    auto v1 = engine::Vector3 {};
    EXPECT_VEC3_EQ(v1, {0.0f, 0.0f, 0.0f});

    // single parameter
    auto v2 = engine::Vector3 {1.0f};
    EXPECT_VEC3_EQ(v2, {1.0f, 1.0f, 1.0f});

    // parameterized
    auto v3 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_VEC3_EQ(v3, {1.0f, 2.0f, 3.0f});
}

TEST(Vector3, ComponentAccess) {
    auto v = engine::Vector3 {1.0f, 2.0f, 3.0f};

    // direct access
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);

    // random-access operator
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);

    EXPECT_DEATH({ v[3]; }, ".*Assertion failed: i >= 0 && i < 3.*");
}

TEST(Vector3, CrossProduct) {
    // positive values
    auto v1 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    auto v2 = engine::Vector3 {4.0f, 5.0f, 6.0f};
    EXPECT_VEC3_EQ(engine::cross(v1, v2), {-3.0f, 6.0f, -3.0f});

    // zero vector
    auto v3 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    auto v4 = engine::Vector3 {0.0f, 0.0f, 0.0f};
    EXPECT_VEC3_EQ(engine::cross(v3, v4), {0.0f, 0.0f, 0.0f});

    // parallel vectors
    auto v5 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    auto v6 = engine::Vector3 {2.0f, 4.0f, 6.0f};
    EXPECT_VEC3_EQ(engine::cross(v5, v6), {0.0f, 0.0f, 0.0f});

    // unit vectors
    auto v7 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    auto v8 = engine::Vector3 {0.0f, 1.0f, 0.0f};
    EXPECT_VEC3_EQ(engine::cross(v7, v8), {0.0f, 0.0f, 1.0f});

    auto v9 = engine::Vector3 {0.0f, 1.0f, 0.0f};
    auto v10 = engine::Vector3 {0.0f, 0.0f, 1.0f};
    EXPECT_VEC3_EQ(engine::cross(v9, v10), {1.0f, 0.0f, 0.0f});

    auto v11 = engine::Vector3 {0.0f, 0.0f, 1.0f};
    auto v12 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    EXPECT_VEC3_EQ(engine::cross(v11, v12), {0.0f, 1.0f, 0.0f});
}

TEST(Vector3, DotProduct) {
    // positive values
    auto v1 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    auto v2 = engine::Vector3 {4.0f, 5.0f, 6.0f};
    EXPECT_FLOAT_EQ(engine::dot(v1, v2), 32.0f);

    // negative values
    auto v3 = engine::Vector3 {-1.0f, -2.0f, -3.0f};
    auto v4 = engine::Vector3 {-4.0f, -5.0f, -6.0f};
    EXPECT_FLOAT_EQ(engine::dot(v3, v4), 32.0f);

    // mixed values
    auto v5 = engine::Vector3 {-1.0f, 2.0f, -3.0f};
    auto v6 = engine::Vector3 {4.0f, -5.0f, 6.0f};
    EXPECT_FLOAT_EQ(engine::dot(v5, v6), -32.0f);

    // zero vector
    auto v7 = engine::Vector3 {0.0f, 0.0f, 0.0f};
    auto v8 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_FLOAT_EQ(engine::dot(v7, v8), 0.0f);

    // large values
    auto v9 = engine::Vector3 {1e6f, 2e6f, 3e6f};
    auto v10 = engine::Vector3 {4e6f, 5e6f, 6e6f};
    EXPECT_FLOAT_EQ(engine::dot(v9, v10), 3.2e+13);

    // perpendicular vectors
    auto v11 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    auto v12 = engine::Vector3 {0.0f, 1.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::dot(v11, v12), 0.0f);

    // parallel vectors
    auto v13 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    auto v14 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::dot(v13, v14), 1.0f);

    // opposite direction
    auto v15 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    auto v16 = engine::Vector3 {-1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::dot(v15, v16), -1.0f);
}

TEST(Vector3, Length) {
    // positive components
    auto v1 = engine::Vector3 {3.0f, 4.0f, 0.0f};
    EXPECT_FLOAT_EQ(v1.length(), 5.0f);

    // negative components
    auto v2 = engine::Vector3 {-3.0f, -4.0f, 0.0f};
    EXPECT_FLOAT_EQ(v2.length(), 5.0f);

    // zero vector
    auto v3 = engine::Vector3 {0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(v3.length(), 0.0f);

    // unit vector
    auto v4 = engine::Vector3 {1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(v4.length(), 1.0f);
}

TEST(Vector3, Addition) {
    // adding non-zero vectors
    auto v1 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    auto v2 = engine::Vector3 {4.0f, 5.0f, 6.0f};
    EXPECT_VEC3_EQ(v1 + v2, engine::Vector3 {5.0f, 7.0f, 9.0f});

    // adding a vector with a zero vector
    auto v3 = engine::Vector3 {7.0f, -3.0f, 2.0f};
    auto v4 = engine::Vector3 {0.0f, 0.0f, 0.0f};
    EXPECT_VEC3_EQ(v3 + v4, engine::Vector3 {7.0f, -3.0f, 2.0f});

    // adding vectors with negative components
    auto v5 = engine::Vector3 {-1.0f, -2.0f, -3.0f};
    auto v6 = engine::Vector3 {-4.0f, -5.0f, -6.0f};
    EXPECT_VEC3_EQ(v5 + v6, engine::Vector3 {-5.0f, -7.0f, -9.0f});
}

TEST(Vector3, Subtraction) {
    // subtracting non-zero vectors
    auto v1 = engine::Vector3 {5.0f, 6.0f, 7.0f};
    auto v2 = engine::Vector3 {3.0f, 2.0f, 1.0f};
    EXPECT_VEC3_EQ(v1 - v2, engine::Vector3 {2.0f, 4.0f, 6.0f});

    // subtracting a vector from itself
    auto v3 = engine::Vector3 {9.0f, 8.0f, 7.0f};
    EXPECT_VEC3_EQ(v3 - v3, engine::Vector3 {0.0f, 0.0f, 0.0f});

    // subtracting a vector from a zero vector
    auto v4 = engine::Vector3 {0.0f, 0.0f, 0.0f};
    auto v5 = engine::Vector3 {2.0f, 4.0f, 6.0f};
    EXPECT_VEC3_EQ(v4 - v5, engine::Vector3 {-2.0f, -4.0f, -6.0f});
}

TEST(Vector3, ScalarMultiplication) {
    // positive scalar
    auto v1 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_VEC3_EQ(v1 * 2.0f, {2.0f, 4.0f, 6.0f});
    EXPECT_VEC3_EQ(2.0f * v1, {2.0f, 4.0f, 6.0f});

    // negative scalar
    auto v2 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_VEC3_EQ(v2 * -1.0f, {-1.0f, -2.0f, -3.0f});
    EXPECT_VEC3_EQ(-1.0f * v2, {-1.0f, -2.0f, -3.0f});

    // zero scalar
    auto v3 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_VEC3_EQ(v3 * 0.0f, {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(0.0f * v3, {0.0f, 0.0f, 0.0f});

    // scalar of one
    auto v4 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_VEC3_EQ(v4 * 1.0f, {1.0f, 2.0f, 3.0f});
    EXPECT_VEC3_EQ(1.0f * v4, {1.0f, 2.0f, 3.0f});
}

TEST(Vector3, ScalarDivision) {
    // positive scalar
    auto v1 = engine::Vector3 {2.0f, 4.0f, 6.0f};
    EXPECT_VEC3_EQ(v1 / 2.0f, {1.0f, 2.0f, 3.0f});

    // negative scalar
    auto v2 = engine::Vector3 {-2.0f, -4.0f, -6.0f};
    EXPECT_VEC3_EQ(v2 / -2.0f, {1.0f, 2.0f, 3.0f});

    // zero scalar
    auto v3 = engine::Vector3 {2.0f, -4.0f, 6.0f};
    auto inf = std::numeric_limits<float>::infinity();
    EXPECT_VEC3_EQ(v3 / 0.0f, {inf, -inf, inf});

    // scalar of one
    auto v4 = engine::Vector3 {1.0f, 2.0f, 3.0f};
    EXPECT_VEC3_EQ(v4 / 1.0f, {1.0f, 2.0f, 3.0f});
}

TEST(Vector3, Normalize) {
    // non-zero vector
    auto v1 = engine::Vector3 {3.0f, 4.0f, 0.0f};
    EXPECT_VEC3_EQ(engine::normalize(v1), {0.6f, 0.8f, 0.0f});

    // normalized vector
    auto v2 = engine::Vector3 {0.6f, 0.8f, 0.0f};
    EXPECT_VEC3_EQ(engine::normalize(v2), {0.6f, 0.8f, 0.0f});

    // zero vector
    auto v3 = engine::Vector3 {0.0f, 0.0f, 0.0f};
    EXPECT_VEC3_EQ(engine::normalize(v3), {0.0f, 0.0f, 0.0f});
}