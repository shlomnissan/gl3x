// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/vector4.hpp>

auto EXPECT_VEC4_EQ(const engine::Vector4&, const engine::Vector4&) -> void;

TEST(Vector4, DefaultConstructor) {
    // default constructor
    auto v1 = engine::Vector4 {};
    EXPECT_VEC4_EQ(v1, {0.0f, 0.0f, 0.0f, 0.0f});

    // single parameter
    auto v2 = engine::Vector4 {1.0f};
    EXPECT_VEC4_EQ(v2, {1.0f, 1.0f, 1.0f, 1.0f});

    // parameterized
    auto v3 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0};
    EXPECT_VEC4_EQ(v3, {1.0f, 2.0f, 3.0f, 4.0});
}

TEST(Vector4, DotProduct) {
    // positive values
    auto v1 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    auto v2 = engine::Vector4 {4.0f, 5.0f, 6.0f, 7.0f};
    EXPECT_FLOAT_EQ(engine::dot(v1, v2), 60.0f);

    // negative values
    auto v3 = engine::Vector4 {-1.0f, -2.0f, -3.0f, -4.0f};
    auto v4 = engine::Vector4 {-4.0f, -5.0f, -6.0f, -7.0f};
    EXPECT_FLOAT_EQ(engine::dot(v3, v4), 60.0f);

    // mixed values
    auto v5 = engine::Vector4 {-1.0f, 2.0f, -3.0f, 4.0f};
    auto v6 = engine::Vector4 {4.0f, -5.0f, 6.0f, -7.0f};
    EXPECT_FLOAT_EQ(engine::dot(v5, v6), -60.0f);

    // zero vector
    auto v7 = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};
    auto v8 = engine::Vector4 {1.0f, 2.0f, 3.0f, 4.0f};
    EXPECT_FLOAT_EQ(engine::dot(v7, v8), 0.0f);

    // large values
    auto v9 = engine::Vector4 {1e6f, 2e6f, 3e6f, 4e6f};
    auto v10 = engine::Vector4 {4e6f, 5e6f, 6e6f, 7e6f};
    EXPECT_FLOAT_EQ(engine::dot(v9, v10), 6e+13);

    // perpendicular vectors
    auto v11 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    auto v12 = engine::Vector4 {0.0f, 1.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::dot(v11, v12), 0.0f);

    // parallel vectors
    auto v13 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    auto v14 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::dot(v13, v14), 1.0f);

    // opposite direction
    auto v15 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    auto v16 = engine::Vector4 {-1.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(engine::dot(v15, v16), -1.0f);
}

TEST(Vector4, Length) {
    // positive components
    auto v1 = engine::Vector4 {3.0f, 4.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(v1.length(), 5.0f);

    // negative components
    auto v2 = engine::Vector4 {-3.0f, -4.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(v2.length(), 5.0f);

    // zero vector
    auto v3 = engine::Vector4 {0.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(v3.length(), 0.0f);

    // unit vector along x
    auto v4 = engine::Vector4 {1.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(v4.length(), 1.0f);

    // unit vector along w
    auto v5 = engine::Vector4 {0.0f, 0.0f, 0.0f, 1.0f};
    EXPECT_FLOAT_EQ(v5.length(), 1.0f);

    // mixed components
    auto v6 = engine::Vector4 {1.0f, 2.0f, 2.0f, 1.0f};
    EXPECT_FLOAT_EQ(v6.length(), std::sqrt(10.0f));
}

auto EXPECT_VEC4_EQ(const engine::Vector4& a, const engine::Vector4& b) -> void {
    EXPECT_EQ(a.x, b.x);
    EXPECT_EQ(a.y, b.y);
    EXPECT_EQ(a.z, b.z);
    EXPECT_EQ(a.w, b.w);
}