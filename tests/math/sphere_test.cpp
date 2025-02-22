// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/sphere.hpp>
#include <engine/math/vector3.hpp>

#pragma region Constructors

TEST(Sphere, DefaultConstructor) {
    const auto sphere = engine::Sphere {};

    EXPECT_VEC3_EQ(sphere.Center(), engine::Vector3::Zero());
    EXPECT_FLOAT_EQ(sphere.Radius(), -1.0f);
}

TEST(Sphere, ConstructorParameterized) {
    const auto sphere = engine::Sphere {
        {1.0f, 1.0f, 1.0f},
        2.0f
    };

    EXPECT_VEC3_EQ(sphere.Center(), {1.0f, 1.0f, 1.0f});
    EXPECT_FLOAT_EQ(sphere.Radius(), 2.0f);
}

#pragma endregion

#pragma region Empty State

TEST(Sphere, Reset) {
    auto sphere = engine::Sphere {1.0f, 2.0f};

    sphere.Reset();

    EXPECT_TRUE(sphere.IsEmpty());
    EXPECT_VEC3_EQ(sphere.Center(), engine::Vector3::Zero());
    EXPECT_FLOAT_EQ(sphere.Radius(), -1.0f);
}

TEST(Sphere, IsEmptyTrue) {
    const auto sphere = engine::Sphere {1.0f, -1.0f};

    EXPECT_TRUE(sphere.IsEmpty());
}

TEST(Sphere, IsEmptyFalse) {
    const auto sphere = engine::Sphere {1.0f, 1.0f};

    EXPECT_FALSE(sphere.IsEmpty());
}

#pragma endregion

#pragma region Expand with Point

// TODO: add tests

#pragma endregion