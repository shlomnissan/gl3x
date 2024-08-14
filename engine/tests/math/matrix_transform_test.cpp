// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix_transform.hpp>

#pragma region Scale

TEST(MatrixTransform, ScaleNonUniformScaling) {
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

TEST(MatrixTransform, ScaleUniformScaling) {
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

// TODO: add test for rotation transform

#pragma endregion

#pragma region Translate

TEST(MatrixTransform, Translate) {
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

TEST(MatrixTransform, LookAtBasicView) {
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

TEST(MatrixTransform, LookAtDifferentUp) {
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

TEST(MatrixTransform, LookAtCollinearEyeAndCenter) {
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