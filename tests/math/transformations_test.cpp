// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <cmath>

#include <engine/math/utilities.hpp>
#include <engine/math/transformations.hpp>

#pragma region Scale

TEST(Transformations, ScaleNonUniformScaling) {
    const auto m = engine::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 4.0f
    };

    EXPECT_MAT4_EQ(engine::scale(m, {2.0f, 3.0f, 4.0f}), {
        1.0f * 2.0f, 2.0f * 3.0f, 3.0f * 4.0f, 4.0f,
        5.0f * 2.0f, 6.0f * 3.0f, 7.0f * 4.0f, 8.0f,
        4.0f * 2.0f, 3.0f * 3.0f, 2.0f * 4.0f, 1.0f,
        8.0f * 2.0f, 7.0f * 3.0f, 6.0f * 4.0f, 4.0f
    });
}

TEST(Transformations, ScaleUniformScaling) {
    const auto m = engine::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 4.0f
    };

    EXPECT_MAT4_EQ(engine::scale(m, 2.0f), {
        1.0f * 2.0f, 2.0f * 2.0f, 3.0f * 2.0f, 4.0f,
        5.0f * 2.0f, 6.0f * 2.0f, 7.0f * 2.0f, 8.0f,
        4.0f * 2.0f, 3.0f * 2.0f, 2.0f * 2.0f, 1.0f,
        8.0f * 2.0f, 7.0f * 2.0f, 6.0f * 2.0f, 4.0f
    });
}

#pragma endregion

#pragma region Rotate

TEST(Transformations, RotateX) {
    const auto m = engine::Matrix4 {1.0f};
    const auto a = engine::math::pi / 6.0f;
    const auto c = std::cos(a);
    const auto s = std::sin(a);

    EXPECT_MAT4_EQ(engine::rotate(m, a, {1.0f, 0.0f, 0.0f}), {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f,    c,   -s, 0.0f,
        0.0f,    s,    c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transformations, RotateY) {
    const auto m = engine::Matrix4 {1.0f};
    const auto a = engine::math::pi / 6.0f;
    const auto c = std::cos(a);
    const auto s = std::sin(a);

    EXPECT_MAT4_EQ(engine::rotate(m, a, {0.0f, 1.0f, 0.0f}), {
           c, 0.0f,    s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
          -s, 0.0f,    c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transformations, RotateZ) {
    const auto m = engine::Matrix4 {1.0f};
    const auto a = engine::math::pi / 6.0f;
    const auto c = std::cos(a);
    const auto s = std::sin(a);

    EXPECT_MAT4_EQ(engine::rotate(m, a, {0.0f, 0.0f, 1.0f}), {
           c,   -s, 0.0f, 0.0f,
           s,    c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transformations, RotateXYZ) {
    const auto a_x = engine::math::pi/ 4.0f;
    const auto a_y = engine::math::pi / 6.0f;
    const auto a_z = engine::math::pi / 3.0f;

    auto m = engine::Matrix4 {1.0f};
    m = engine::rotate(m, a_x, {1.0f, 0.0f, 0.0f});
    m = engine::rotate(m, a_y, {0.0f, 1.0f, 0.0f});
    m = engine::rotate(m, a_z, {0.0f, 0.0f, 1.0f});

    EXPECT_VEC4_EQ(m[0], {
        std::cos(a_y) * std::cos(a_z),
        std::cos(a_x) * std::sin(a_z) + std::cos(a_z) * std::sin(a_x) * std::sin(a_y),
        std::sin(a_x) * std::sin(a_z) - std::cos(a_x) * std::cos(a_z) * std::sin(a_y),
        0.0f
    });
    EXPECT_VEC4_EQ(m[1], {
       -std::cos(a_y) * std::sin(a_z),
        std::cos(a_x) * std::cos(a_z) - std::sin(a_x) * std::sin(a_y) * std::sin(a_z),
        std::cos(a_x) * std::sin(a_z) * std::sin(a_y) + std::cos(a_z) * std::sin(a_x),
        0.0f
    });
    EXPECT_VEC4_EQ(m[2], {
        std::sin(a_y),
       -std::cos(a_y) * std::sin(a_x),
        std::cos(a_x) * std::cos(a_y),
        0.0f
    });
    EXPECT_VEC4_EQ(m[3], {0.0f, 0.0f, 0.0f, 1.0f});
}

#pragma endregion

#pragma region Translate

TEST(Transformations, Translate) {
    const auto m = engine::Matrix4 {1.0f};

    EXPECT_MAT4_EQ(engine::translate(m, {2.0f, 3.0f, 4.0f}), {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 1.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

#pragma endregion

#pragma region Look At

TEST(Transformations, LookAtBasicView) {
    const auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    const auto center = engine::Vector3 {0.0f, 0.0f, 0.0f};
    const auto up = engine::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        1.0f, 0.0f, 0.0f,  0.0f,
        0.0f, 1.0f, 0.0f,  0.0f,
        0.0f, 0.0f, 1.0f, -5.0f,
        0.0f, 0.0f, 0.0f,  1.0f
    });
}

TEST(Transformations, LookAtDifferentUp) {
    const auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    const auto center = engine::Vector3 {0.0f, 0.0f, 0.0f};
    const auto up = engine::Vector3 {0.0f, 0.5f, 1.0f};

    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        1.0f, 0.0f, 0.0f,  0.0f,
        0.0f, 1.0f, 0.0f,  0.0f,
        0.0f, 0.0f, 1.0f, -5.0f,
        0.0f, 0.0f, 0.0f,  1.0f
    });
}

TEST(Transformations, LookAtCollinearEyeAndCenter) {
    const auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    const auto center = engine::Vector3 {0.0f, 0.0f, 10.0f};
    const auto up = engine::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 5.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

#pragma endregion