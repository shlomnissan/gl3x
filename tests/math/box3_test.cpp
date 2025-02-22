// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <limits>

#include <engine/math/box3.hpp>
#include <engine/math/matrix4.hpp>
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

#pragma region Empty State

TEST(Box3, Reset) {
    auto box = engine::Box3 {
        {-1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.Reset();

    EXPECT_TRUE(box.IsEmpty());
    EXPECT_VEC3_EQ(box.Min(), std::numeric_limits<float>::max());
    EXPECT_VEC3_EQ(box.Max(), std::numeric_limits<float>::lowest());
}

TEST(Box3, IsEmptyTrue) {
    const auto box = engine::Box3 {
        {1.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, 0.0f}
    };

    EXPECT_TRUE(box.IsEmpty());
}

TEST(Box3, IsEmptyFalse) {
    const auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    EXPECT_FALSE(box.IsEmpty());
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

#pragma region Expand with Point

TEST(Box3, ExpandWithPoint) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({1.0f, 2.0f, -2.0f});

    EXPECT_VEC3_EQ(box.Min(), {0.0f, 0.0f, -2.0f});
    EXPECT_VEC3_EQ(box.Max(), {1.0f, 2.0f, 1.0f});
}

TEST(Box3, ExpandWithPointInsideBox) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({0.5f, 0.5f, 0.5f});

    EXPECT_VEC3_EQ(box.Min(), {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.Max(), {1.0f, 1.0f, 1.0f});
}

TEST(Box3, ExpandWithPointOnMinMax) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({0.0f, 0.0f, 0.0f});
    box.ExpandWithPoint({1.0f, 1.0f, 1.0f});

    EXPECT_VEC3_EQ(box.Min(), {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.Max(), {1.0f, 1.0f, 1.0f});
}

TEST(Box3, ExpandWithMultiplePoints) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    box.ExpandWithPoint({2.0f, 2.0f, 2.0f});
    box.ExpandWithPoint({-1.0f, -1.0f, -1.0f});

    EXPECT_VEC3_EQ(box.Min(), {-1.0f, -1.0f, -1.0f});
    EXPECT_VEC3_EQ(box.Max(), {2.0f, 2.0f, 2.0f});
}

#pragma endregion

#pragma region Apply Transform

TEST(Box3, TransformWithIdentityMatrix) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    const auto transform = engine::Matrix4::Identity();

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.Min(), {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.Max(), {1.0f, 1.0f, 1.0f});
}

TEST(Box3, TransformWithTranslation) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    const auto transform = engine::Matrix4 {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 1.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.Min(), {2.0f, 3.0f, 4.0f});
    EXPECT_VEC3_EQ(box.Max(), {3.0f, 4.0f, 5.0f});
}

TEST(Box3, TransformWithScale) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    const auto transform = engine::Matrix4 {
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.Min(), {0.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.Max(), {2.0f, 1.0f, 3.0f});
}

TEST(Box3, TransformWithRotation) {
    auto box = engine::Box3 {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    // Rotate 90 degrees around the z-axis
    const auto transform = engine::Matrix4 {
        0.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  0.0f, 0.0f, 1.0f
    };

    box.ApplyTransform(transform);

    EXPECT_VEC3_EQ(box.Min(), {-1.0f, 0.0f, 0.0f});
    EXPECT_VEC3_EQ(box.Max(), {0.0f, 1.0f, 1.0f});
}

#pragma endregion