// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/transform.hpp>
#include <engine/math/vector3.hpp>

#pragma region Equality Operator

TEST(Transform, EqualityOperator) {
    auto t1 = engine::Transform {};
    auto t2 = engine::Transform {};
    auto t3 = engine::Transform {};

    t3.Scale(0.3f);
    t3.Rotate(engine::Vector3::X(), 0.5f);


    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

TEST(Transform, InequalityOperator) {
    auto t1 = engine::Transform {};
    auto t2 = engine::Transform {};
    auto t3 = engine::Transform {};

    t3.Scale(0.3f);
    t3.Rotate(engine::Vector3::X(), 0.5f);


    EXPECT_FALSE(t1 != t2);
    EXPECT_TRUE(t1 != t3);
}

#pragma endregion