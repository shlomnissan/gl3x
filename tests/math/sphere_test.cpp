// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix4.hpp>
#include <engine/math/sphere.hpp>
#include <engine/math/vector3.hpp>

#pragma region Constructors

TEST(Sphere, DefaultConstructor) {
    const auto sphere = engine::Sphere {};

    EXPECT_VEC3_EQ(sphere.center, engine::Vector3::Zero());
    EXPECT_FLOAT_EQ(sphere.radius, -1.0f);
}

TEST(Sphere, ConstructorParameterized) {
    const auto sphere = engine::Sphere {
        {1.0f, 1.0f, 1.0f},
        2.0f
    };

    EXPECT_VEC3_EQ(sphere.center, {1.0f, 1.0f, 1.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 2.0f);
}

#pragma endregion

#pragma region Empty State

TEST(Sphere, Reset) {
    auto sphere = engine::Sphere {1.0f, 2.0f};

    sphere.Reset();

    EXPECT_TRUE(sphere.IsEmpty());
    EXPECT_VEC3_EQ(sphere.center, engine::Vector3::Zero());
    EXPECT_FLOAT_EQ(sphere.radius, -1.0f);
}

TEST(Sphere, IsEmptyTrue) {
    const auto sphere = engine::Sphere {};

    EXPECT_TRUE(sphere.IsEmpty());
}

TEST(Sphere, IsEmptyFalse) {
    const auto sphere = engine::Sphere {1.0f, 1.0f};

    EXPECT_FALSE(sphere.IsEmpty());
}

#pragma endregion

#pragma region Expand with Point

TEST(Sphere, ExpandWithPointEmptySphere) {
    auto sphere = engine::Sphere {};

    sphere.ExpandWithPoint({1.0f, 1.0f, 1.0f});

    EXPECT_VEC3_EQ(sphere.center, {1.0f, 1.0f, 1.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 0.0f);
}

TEST(Sphere, ExpandWithPointInsideSphere) {
    auto sphere = engine::Sphere {engine::Vector3::Zero(), 5.0f};
    const auto point = engine::Vector3 {1.0f, 1.0f, 1.0f};

    sphere.ExpandWithPoint(point);

    EXPECT_VEC3_EQ(sphere.center, engine::Vector3::Zero());
    EXPECT_FLOAT_EQ(sphere.radius, 5.0f);
}

TEST(Sphere, ExpandWithPointOnSphereSurface) {
    auto sphere = engine::Sphere {engine::Vector3::Zero(), 1.0f};
    const auto point = engine::Vector3 {1.0f, 0.0f, 0.0f};

    sphere.ExpandWithPoint(point);

    EXPECT_VEC3_EQ(sphere.center, engine::Vector3::Zero());
    EXPECT_FLOAT_EQ(sphere.radius, 1.0f);
}

TEST(Sphere, ExpandWithPointOutsideSphere) {
    auto sphere = engine::Sphere {engine::Vector3::Zero(), 1.0f};
    const auto point = engine::Vector3 {2.0f, 0.0f, 0.0f};

    sphere.ExpandWithPoint(point);

    EXPECT_VEC3_EQ(sphere.center, {0.5f, 0.0f, 0.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 1.5f);
}

#pragma endregion

#pragma region Apply Transform

TEST(Sphere, TransformWithIdentityMatrix) {
    auto sphere = engine::Sphere {{1.0f, 2.0f, 3.0f}, 4.0f};
    const auto transform = engine::Matrix4::Identity();

    sphere.ApplyTransform(transform);

    EXPECT_VEC3_EQ(sphere.center, {1.0f, 2.0f, 3.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 4.0f);
}

TEST(Sphere, TransformWithTranslation) {
    auto sphere = engine::Sphere {{1.0f, 2.0f, 3.0f}, 4.0f};
    const auto transform = engine::Matrix4 {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 1.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    sphere.ApplyTransform(transform);

    EXPECT_VEC3_EQ(sphere.center, {3.0f, 5.0f, 7.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 4.0f);
}

TEST(Sphere, TransformWithScale) {
    auto sphere = engine::Sphere {{1.0f, 2.0f, 3.0f}, 4.0f};
    const auto transform = engine::Matrix4 {
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    sphere.ApplyTransform(transform);

    EXPECT_VEC3_EQ(sphere.center, {2.0f, 4.0f, 6.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 8.0f);
}

TEST(Sphere, TransformWithRotation) {
    auto sphere = engine::Sphere {{1.0f, 0.0f, 0.0f}, 4.0f};

    // Rotate 90 degrees around the z-axis
    const auto transform = engine::Matrix4 {
        0.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  0.0f, 0.0f, 1.0f
    };

    sphere.ApplyTransform(transform);

    EXPECT_VEC3_EQ(sphere.center, {0.0f, 1.0f, 0.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 4.0f);
}

#pragma endregion

#pragma region Translate

TEST(Sphere, Translate) {
    auto sphere = engine::Sphere {{1.0f, 2.0f, 3.0f}, 4.0f};
    sphere.Translate({1.0f, 2.0f, 3.0f});

    EXPECT_VEC3_EQ(sphere.center, {2.0f, 4.0f, 6.0f});
    EXPECT_FLOAT_EQ(sphere.radius, 4.0f);
}

#pragma endregion