// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/matrix_transform.hpp>

TEST(MatrixTransformLookAt, BasicViewMatrix) {
    auto eye = engine::Vector3 {0.0f, 0.0f, 5.0f};
    auto center = engine::Vector3 {0.0f, 0.0f, 0.0f};
    auto up = engine::Vector3 {0.0f, 1.0f, 0.0f};

    auto output = engine::LookAt(eye, center, up);
    EXPECT_MAT4_EQ(output, {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, -5.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}