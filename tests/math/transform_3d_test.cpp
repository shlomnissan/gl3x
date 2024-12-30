// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/transform_3d.hpp>
#include <engine/math/utilities.hpp>

#include <cmath>

#pragma region Transformations

// TODO: Translate

// TODO: Scale

// TODO: Rotate

// TODO: TSR

// TODO: LookAtWithIdentity

// TODO: LookAtWithTransformations

#pragma endregion

#pragma region Cumulative Transformations

TEST(Transform3D, Translate) {
    auto t = engine::Transform3D {};
    t.Translate({2.0f, 1.0f, 3.0f});
    t.Translate({1.0f, 1.0f, 0.0f});

    EXPECT_VEC3_EQ(t.GetPosition(), {3.0f, 2.0f, 3.0f});
    EXPECT_MAT4_EQ(t.Get(), {
        1.0f, 0.0f, 0.0f, 3.0f,
        0.0f, 1.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3D, Scale) {
    auto t = engine::Transform3D {};
    t.Scale({2.0f, 2.0f, 2.0f});
    t.Scale({3.0f, 3.0f, 2.0f});

    EXPECT_VEC3_EQ(t.GetScale(), {6.0f, 6.0f, 4.0f});
    EXPECT_MAT4_EQ(t.Get(), {
        6.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 6.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 4.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3D, RotateX) {
    auto t = engine::Transform3D {};
    t.Rotate(engine::Vector3::Right(), engine::math::half_pi);
    t.Rotate(engine::Vector3::Right(), 0.1f);

    auto c = std::cos(t.GetRotation().pitch);
    auto s = std::sin(t.GetRotation().pitch);
    EXPECT_EQ(t.GetRotation().pitch, engine::math::half_pi + 0.1f);
    EXPECT_MAT4_EQ(t.Get(), {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, c, -s, 0.0f,
        0.0f, s, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3D, RotateY) {
    auto t = engine::Transform3D {};
    t.Rotate(engine::Vector3::Up(), engine::math::half_pi);
    t.Rotate(engine::Vector3::Up(), 0.1f);

    auto c = std::cos(t.GetRotation().yaw);
    auto s = std::sin(t.GetRotation().yaw);
    EXPECT_EQ(t.GetRotation().yaw, engine::math::half_pi + 0.1f);
    EXPECT_MAT4_EQ(t.Get(), {
        c, 0.0f, s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -s, 0.0f, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3D, RotateZ) {
    auto t = engine::Transform3D {};
    t.Rotate(engine::Vector3::Forward(), engine::math::half_pi);
    t.Rotate(engine::Vector3::Forward(), 0.1f);

    auto c = std::cos(t.GetRotation().roll);
    auto s = std::sin(t.GetRotation().roll);
    EXPECT_EQ(t.GetRotation().roll, engine::math::half_pi + 0.1f);
    EXPECT_MAT4_EQ(t.Get(), {
        c, -s, 0.0f, 0.0f,
        s, c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

#pragma endregion