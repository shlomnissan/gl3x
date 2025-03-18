// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/frustum.hpp>
#include <engine/nodes/camera_orthographic.hpp>
#include <engine/nodes/camera_perspective.hpp>

#pragma region Fixtures

class FrustumTest : public ::testing::Test {
protected:
    std::shared_ptr<engine::CameraOrthographic> orthographic_camera =
    engine::CameraOrthographic::Create({
        .left = -1.0f,
        .right = 1.0f,
        .top = 1.0f,
        .bottom = -1.0f,
        .near = 1.0f,
        .far = 100.0f
    });

    std::shared_ptr<engine::CameraPerspective> perspective_camera_ =
    engine::CameraPerspective::Create({
        .fov = 90.0f,
        .aspect = 1.0f,
        .near = 1.0f,
        .far = 100.0f
    });
};

#pragma endregion

#pragma region Contains Point

TEST_F(FrustumTest, ContainsPointWithOrthographicCamera) {
    const auto frustum = engine::Frustum(orthographic_camera->projection_transform);

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

TEST_F(FrustumTest, ContainsPointWithPerspectiveCamera) {
    const auto frustum = engine::Frustum(perspective_camera_->projection_transform);

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
    EXPECT_TRUE(true);
}

TEST(Frustum, IntersectsWithBox3) {
    // TODO: implement
    EXPECT_TRUE(true);
}

#pragma endregion