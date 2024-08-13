// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix_transform.hpp>

TEST(MatrixTransform, Scale) {
    // non-uniform scaling
    auto m1 = engine::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 4.0f
    };
    EXPECT_MAT4_EQ(engine::scale(m1, {2.0f, 3.0f, 4.0f}), {
        1.0f * 2.0f, 2.0f * 3.0f, 3.0f * 4.0f, 4.0f,
        5.0f * 2.0f, 6.0f * 3.0f, 7.0f * 4.0f, 8.0f,
        4.0f * 2.0f, 3.0f * 3.0f, 2.0f * 4.0f, 1.0f,
        8.0f * 2.0f, 7.0f * 3.0f, 6.0f * 4.0f, 4.0f
    });

    // uniform scaling
    auto m2 = engine::Matrix4 {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        4.0f, 3.0f, 2.0f, 1.0f,
        8.0f, 7.0f, 6.0f, 4.0f
    };
    EXPECT_MAT4_EQ(engine::scale(m2, 2.0f), {
        1.0f * 2.0f, 2.0f * 2.0f, 3.0f * 2.0f, 4.0f,
        5.0f * 2.0f, 6.0f * 2.0f, 7.0f * 2.0f, 8.0f,
        4.0f * 2.0f, 3.0f * 2.0f, 2.0f * 2.0f, 1.0f,
        8.0f * 2.0f, 7.0f * 2.0f, 6.0f * 2.0f, 4.0f
    });
}

TEST(MatrixTransform, Translate) {
    auto m = engine::Matrix4 {1.0f};

    EXPECT_MAT4_EQ(engine::translate(m, {2.0f, 3.0f, 4.0f}), {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 1.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(MatrixTransform, LookAt) {
    // basic view matrix
    auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    auto center = engine::Vector3 {0.0f, 0.0f, 0.0f};
    auto up = engine::Vector3 {0.0f, 1.0f, 0.0f};
    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        1.0f, 0.0f, 0.0f,  0.0f,
        0.0f, 1.0f, 0.0f,  0.0f,
        0.0f, 0.0f, 1.0f, -5.0f,
        0.0f, 0.0f, 0.0f,  1.0f
    });

    // different up vector
    eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    center = engine::Vector3 {0.0f, 0.0f, 0.0f};
    up = engine::Vector3 {0.0f, 0.5f, 1.0f};
    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        1.0f, 0.0f, 0.0f,  0.0f,
        0.0f, 1.0f, 0.0f,  0.0f,
        0.0f, 0.0f, 1.0f, -5.0f,
        0.0f, 0.0f, 0.0f,  1.0f
    });

    // collinear eye and center
    eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    center = engine::Vector3 {0.0f, 0.0f, 10.0f};
    up = engine::Vector3 {0.0f, 1.0f, 0.0f};
    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 5.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}