// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/frustum.hpp>
#include <engine/nodes/camera_orthographic.hpp>
#include <engine/nodes/camera_perspective.hpp>

#pragma region Contains Point

TEST(Frustum, ContainsPointWithOrthographicCamera) {
    const auto camera = engine::CameraOrthographic::Create({
        .left = -1.0f,
        .right = 1.0f,
        .top = 1.0f,
        .bottom = -1.0f,
        .near = 1.0f,
        .far = 100.0f
    });
    const auto frustum = engine::Frustum(camera->projection_transform);

    EXPECT_FALSE(frustum.ContainsPoint({-1.1f, -1.1f, -1.001f}));
    EXPECT_FALSE(frustum.ContainsPoint({-1.1f, -1.1f, -100.1f}));
    EXPECT_FALSE(frustum.ContainsPoint({0.0f, 0.0f, -101.0f}));
    EXPECT_FALSE(frustum.ContainsPoint({0.0f, 0.0f, 0.0f}));
    EXPECT_FALSE(frustum.ContainsPoint({1.1f, 1.1f, -1.001f}));
    EXPECT_FALSE(frustum.ContainsPoint({1.1f, 1.1f, -100.1f}));
    EXPECT_TRUE(frustum.ContainsPoint({-1.0f, -1.0f, -1.001f}));
    EXPECT_TRUE(frustum.ContainsPoint({-1.0f, -1.0f, -100.0f}));
    EXPECT_TRUE(frustum.ContainsPoint({0.0f, 0.0f, -1.001f}));
    EXPECT_TRUE(frustum.ContainsPoint({0.0f, 0.0f, -100.0f}));
    EXPECT_TRUE(frustum.ContainsPoint({0.0f, 0.0f, -50.0f}));
    EXPECT_TRUE(frustum.ContainsPoint({1.0f, 1.0f, -1.001f}));
    EXPECT_TRUE(frustum.ContainsPoint({1.0f, 1.0f, -100.0f}));
}

TEST(Frustum, ContainsPointWithPerspectiveCamera) {
    const auto camera = engine::CameraPerspective::Create({
        .fov = 90.0f,
        .aspect = 1.0f,
        .near = 1.0f,
        .far = 100.0f
    });
    const auto frustum = engine::Frustum(camera->projection_transform);

    EXPECT_FALSE(frustum.ContainsPoint({-1.1f, -1.1f, -1.001f}));
    EXPECT_FALSE(frustum.ContainsPoint({-100.1f, -100.1f, -100.1f}));
    EXPECT_FALSE(frustum.ContainsPoint({0.0f, 0.0f, -101.0f}));
    EXPECT_FALSE(frustum.ContainsPoint({0.0f, 0.0f, 0.0f}));
    EXPECT_FALSE(frustum.ContainsPoint({1.1f, 1.1f, -1.001f}));
    EXPECT_FALSE(frustum.ContainsPoint({100.1f, 100.1f, -100.1f}));
    EXPECT_TRUE(frustum.ContainsPoint({-1.0f, -1.0f, -1.001f}));
    EXPECT_TRUE(frustum.ContainsPoint({-99.999f, -99.999f, -99.999f}));
    EXPECT_TRUE(frustum.ContainsPoint({0.0f, 0.0f, -1.001f}));
    EXPECT_TRUE(frustum.ContainsPoint({0.0f, 0.0f, -50.0f}));
    EXPECT_TRUE(frustum.ContainsPoint({0.0f, 0.0f, -99.999f}));
    EXPECT_TRUE(frustum.ContainsPoint({1.0f, 1.0f, -1.001f}));
    EXPECT_TRUE(frustum.ContainsPoint({99.999f, 99.999f, -99.999f}));
}

#pragma endregion

#pragma region Intersections

TEST(Frustum, IntersectsWithSphere) {
    // TODO: implement
    EXPECT_TRUE(true);
}

TEST(Frustum, IntersectsWithBox3) {
    // TODO: implement
    EXPECT_TRUE(true);
}

#pragma endregion