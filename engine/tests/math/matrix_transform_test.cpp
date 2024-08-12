// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix_transform.hpp>

TEST(MatrixTransformScale, NonUniformScaling) {
    auto m = engine::Matrix4 {
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

TEST(MatrixTransformScale, UniformScaling) {
    auto m = engine::Matrix4 {
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

TEST(MatrixTransformTranslate, BasicTranslation) {
    auto m = engine::Matrix4 {1.0f};

    EXPECT_MAT4_EQ(engine::translate(m, {2.0f, 3.0f, 4.0f}), {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 1.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(MatrixTransformLookAt, BasicViewMatrix) {
    auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    auto center = engine::Vector3 {0.0f, 0.0f, 0.0f};
    auto up = engine::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        1.0f, 0.0f, 0.0f,  0.0f,
        0.0f, 1.0f, 0.0f,  0.0f,
        0.0f, 0.0f, 1.0f, -5.0f,
        0.0f, 0.0f, 0.0f,  1.0f
    });
}

TEST(MatrixTransformLookAt, DifferentUpVector) {
    auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    auto center = engine::Vector3 {0.0f, 0.0f, 0.0f};
    auto up = engine::Vector3 {0.0f, 0.5f, 1.0f};

    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        1.0f, 0.0f, 0.0f,  0.0f,
        0.0f, 1.0f, 0.0f,  0.0f,
        0.0f, 0.0f, 1.0f, -5.0f,
        0.0f, 0.0f, 0.0f,  1.0f
    });
}

TEST(MatrixTransformLookAt, CollinearEyeAndCenter) {
    auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    auto center = engine::Vector3 {0.0f, 0.0f, 10.0f};
    auto up = engine::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_MAT4_EQ(engine::look_at(eye, center, up), {
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 5.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}