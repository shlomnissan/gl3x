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
    t3.Rotate(engine::Vector3::Right(), 0.5f);


    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

TEST(Transform, InequalityOperator) {
    auto t1 = engine::Transform {};
    auto t2 = engine::Transform {};
    auto t3 = engine::Transform {};

    t3.Scale(0.3f);
    t3.Rotate(engine::Vector3::Right(), 0.5f);

    EXPECT_FALSE(t1 != t2);
    EXPECT_TRUE(t1 != t3);
}

#pragma endregion

#pragma region Transform Multiplication

TEST(Transform, MultiplicationWithTranslationAndScale) {
    auto t1 = engine::Transform {};
    t1.Translate({1.0f, 2.0f, 3.0f});

    auto t2 = engine::Transform {};
    t2.Scale(0.5f);

    auto expected_output = engine::Transform {};
    expected_output.Translate({1.0f, 2.0f, 3.0f});
    expected_output.Scale(0.5f);

    EXPECT_EQ(t1 * t2, expected_output);
}

TEST(Transform, MultiplicationWithTranslationAndRotation) {
    auto t1 = engine::Transform {};
    t1.Translate({1.0f, 2.0f, 3.0f});

    auto t2 = engine::Transform {};
    t2.Rotate(engine::Vector3::Right(), 0.5f);

    auto expected_output = engine::Transform {};
    expected_output.Translate({1.0f, 2.0f, 3.0f});
    expected_output.Rotate(engine::Vector3::Right(), 0.5f);

    EXPECT_EQ(t1 * t2, expected_output);
}

TEST(Transform, MultiplicationWithAllTransformations) {
    auto t1 = engine::Transform {};
    t1.Translate(engine::Vector3(1.0f, 2.0f, 3.0f));
    t1.Scale(2.0f);
    t1.Rotate(engine::Vector3::Right(), 0.5f);

    auto t2 = engine::Transform {};
    t2.Translate(engine::Vector3(4.0f, 5.0f, 6.0f));
    t2.Scale(0.5f);
    t2.Rotate(engine::Vector3::Up(), 0.3f);

    auto expected_output = engine::Transform {};
    expected_output.Translate(engine::Vector3(1.0f, 2.0f, 3.0f));
    expected_output.Scale(2.0f);
    expected_output.Rotate(engine::Vector3::Right(), 0.5f);
    expected_output.Translate(engine::Vector3(4.0f, 5.0f, 6.0f));
    expected_output.Scale(0.5f);
    expected_output.Rotate(engine::Vector3::Up(), 0.3f);

    EXPECT_EQ(t1 * t2, expected_output);
}

#pragma endregion