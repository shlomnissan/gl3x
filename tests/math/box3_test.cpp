// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <limits>

#include <engine/math/box3.hpp>
#include <engine/math/vector3.hpp>

#pragma region Constructors

TEST(Box3, DefaultConstructor) {
    const auto box = engine::Box3 {};

    EXPECT_VEC3_EQ(box.Min(), std::numeric_limits<float>::max());
    EXPECT_VEC3_EQ(box.Max(), std::numeric_limits<float>::lowest());
}

TEST(Vector3, ConstructorParameterized) {
    const auto box = engine::Box3 {
        {-1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    EXPECT_VEC3_EQ(box.Min(), {-1.0f, -1.0f, -1.0f});
    EXPECT_VEC3_EQ(box.Max(), {1.0f, 1.0f, 1.0f});
}

#pragma endregion

#pragma region Center

TEST(Box3, CenterWithNegativeAndPositiveValues) {
    const auto box = engine::Box3 {
        {0.0f, 0.0f, -1.0f},
        {1.0f, 1.0f, 2.0f}
    };

    EXPECT_VEC3_EQ(box.Center(), {0.5f, 0.5f, 0.5f});
}

TEST(Box3, CenterWithSameValues) {
    const auto box = engine::Box3 {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    EXPECT_VEC3_EQ(box.Center(), {1.0f, 1.0f, 1.0f});
}

TEST(Box3, CenterWithZeroValues) {
    const auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}
    };

    EXPECT_VEC3_EQ(box.Center(), {0.0f, 0.0f, 0.0f});
}

#pragma endregion