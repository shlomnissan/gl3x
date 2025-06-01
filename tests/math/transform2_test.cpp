// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gleam/math/transform2.hpp>
#include <gleam/math/utilities.hpp>

#include <cmath>

#pragma region Transformations

TEST(Transform2, Translate) {
    auto t = engine::Transform2 {};
    t.Translate({2.0f, 1.0f});

    EXPECT_VEC2_EQ(t.GetPosition(), {2.0f, 1.0f});
    EXPECT_MAT3_EQ(t.Get(), {
        1.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, Scale) {
    auto t = engine::Transform2 {};
    t.Scale({2.0f, 1.0f});

    EXPECT_VEC2_EQ(t.GetScale(), {2.0f, 1.0f});
    EXPECT_MAT3_EQ(t.Get(), {
        2.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, Rotate) {
    auto t = engine::Transform2 {};
    t.Rotate(engine::math::half_pi);

    auto c = std::cos(t.GetRotation());
    auto s = std::sin(t.GetRotation());
    EXPECT_EQ(t.GetRotation(), engine::math::half_pi);
    EXPECT_MAT3_EQ(t.Get(), {
        c, s, 0.0f,
        -s, c, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, TransformationsWithOffset) {
    auto t = engine::Transform2 {};
    t.SetCenter({0.5, 0.5f});
    t.Translate({2.0f, 3.0f});
    t.Scale({2.0f, 2.0f});
    t.Rotate(engine::math::half_pi);

    auto c = std::cos(t.GetRotation()) * t.GetScale().x;
    auto s = std::sin(t.GetRotation()) * t.GetScale().y;
    EXPECT_VEC2_EQ(t.GetCenter(), {0.5f, 0.5f});
    EXPECT_VEC2_EQ(t.GetPosition(), {2.0f, 3.0f});
    EXPECT_VEC2_EQ(t.GetScale(), {2.0f, 2.0f});
    EXPECT_EQ(t.GetRotation(), engine::math::half_pi);
    EXPECT_MAT3_EQ(t.Get(), {
        c, s, 1.5f,
        -s, c, 4.5f,
        0.0f, 0.0f, 1.0f
    });
}

#pragma endregion