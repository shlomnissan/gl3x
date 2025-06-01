// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <limits>

#include <gleam/math/box3.hpp>
#include <gleam/math/matrix4.hpp>
#include <gleam/math/vector3.hpp>

#pragma region Constructors

TEST(Box3, DefaultConstructor) {
    const auto box = gleam::Box3 {};

    EXPECT_VEC3_EQ(box.min, std::numeric_limits<float>::max());
    EXPECT_VEC3_EQ(box.max, std::numeric_limits<float>::lowest());
}

TEST(Vector3, ConstructorParameterized) {
    const auto box = gleam::Box3 {
        {-1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    EXPECT_VEC3_EQ(box.min, {-1.0f, -1.0f, -1.0f});
    EXPECT_VEC3_EQ(box.max, {1.0f, 1.0f, 1.0f});
}

#pragma endregion

#pragma region Empty State

TEST(Box3, Reset) {
    auto box = gleam::Box3 {
        {-1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.Reset();

    EXPECT_TRUE(box.IsEmpty());
    EXPECT_VEC3_EQ(box.min, std::numeric_limits<float>::max());
    EXPECT_VEC3_EQ(box.max, std::numeric_limits<float>::lowest());
}

TEST(Box3, IsEmptyTrue) {
    const auto box = gleam::Box3 {
        {1.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, 0.0f}
    };

    EXPECT_TRUE(box.IsEmpty());
}

TEST(Box3, IsEmptyFalse) {
    const auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    EXPECT_FALSE(box.IsEmpty());
}

#pragma endregion

#pragma region Center

TEST(Box3, CenterWithNegativeAndPositiveValues) {
    const auto box = gleam::Box3 {
        {0.0f, 0.0f, -1.0f},
        {1.0f, 1.0f, 2.0f}
    };

    EXPECT_VEC3_EQ(box.Center(), {0.5f, 0.5f, 0.5f});
}

TEST(Box3, CenterWithSameValues) {
    const auto box = gleam::Box3 {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    EXPECT_VEC3_EQ(box.Center(), {1.0f, 1.0f, 1.0f});
}

TEST(Box3, CenterWithZeroValues) {
    const auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}
    };

    EXPECT_VEC3_EQ(box.Center(), {0.0f, 0.0f, 0.0f});
}

#pragma endregion

#pragma region Expand with Point

TEST(Box3, ExpandWithPoint) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({1.0f, 2.0f, -2.0f});

    EXPECT_VEC3_EQ(box.min, {0.0f, 0.0f, -2.0f});
    EXPECT_VEC3_EQ(box.max, {1.0f, 2.0f, 1.0f});
}

TEST(Box3, ExpandWithPointInsideBox) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({0.5f, 0.5f, 0.5f});

    EXPECT_VEC3_EQ(box.min, {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.max, {1.0f, 1.0f, 1.0f});
}

TEST(Box3, ExpandWithPointOnMinMax) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({0.0f, 0.0f, 0.0f});
    box.ExpandWithPoint({1.0f, 1.0f, 1.0f});

    EXPECT_VEC3_EQ(box.min, {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.max, {1.0f, 1.0f, 1.0f});
}

TEST(Box3, ExpandWithMultiplePoints) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({2.0f, 2.0f, 2.0f});
    box.ExpandWithPoint({-1.0f, -1.0f, -1.0f});

    EXPECT_VEC3_EQ(box.min, {-1.0f, -1.0f, -1.0f});
    EXPECT_VEC3_EQ(box.max, {2.0f, 2.0f, 2.0f});
}

#pragma endregion

#pragma region Apply Transform

TEST(Box3, TransformWithIdentityMatrix) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    const auto transform = gleam::Matrix4::Identity();

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.min, {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.max, {1.0f, 1.0f, 1.0f});
}

TEST(Box3, TransformWithTranslation) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    const auto transform = gleam::Matrix4 {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 1.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.min, {2.0f, 3.0f, 4.0f});
    EXPECT_VEC3_EQ(box.max, {3.0f, 4.0f, 5.0f});
}

TEST(Box3, TransformWithScale) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    const auto transform = gleam::Matrix4 {
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.min, {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.max, {2.0f, 1.0f, 3.0f});
}

TEST(Box3, TransformWithRotation) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    // Rotate 90 degrees around the z-axis
    const auto transform = gleam::Matrix4 {
        0.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  0.0f, 0.0f, 1.0f
    };

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.min, {-1.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.max, {0.0f, 1.0f, 1.0f});
}

#pragma endregion

#pragma region Translate

TEST(Box3, Translate) {
    auto box = gleam::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.Translate({1.0f, 2.0f, 3.0f});

    EXPECT_VEC3_EQ(box.min, {1.0f, 2.0f, 3.0f});
    EXPECT_VEC3_EQ(box.max, {2.0f, 3.0f, 4.0f});
}

#pragma endregion