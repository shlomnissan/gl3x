// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/plane.hpp>

#pragma region Constructors

TEST(Plane, DefaultConstructor) {
    auto plane = engine::Plane {};

    EXPECT_EQ(plane.Normal(), engine::Vector3::Up());
    EXPECT_EQ(plane.Distance(), 0.0f);
}

TEST(Plane, ConstructorParameterized) {
    auto plane = engine::Plane {engine::Vector3::Right(), 1.0f};

    EXPECT_EQ(plane.Normal(), engine::Vector3::Right());
    EXPECT_EQ(plane.Distance(), 1.0f);
}

#pragma endregion