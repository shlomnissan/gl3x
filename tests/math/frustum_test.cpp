// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gleam/math/frustum.hpp>
#include <gleam/nodes/camera_orthographic.hpp>
#include <gleam/nodes/camera_perspective.hpp>

#pragma region Fixtures

class FrustumTest : public ::testing::Test {
protected:
    std::shared_ptr<gleam::CameraOrthographic> orthographic_camera =
    gleam::CameraOrthographic::Create({
        .left = -1.0f,
        .right = 1.0f,
        .top = 1.0f,
        .bottom = -1.0f,
        .near = 1.0f,
        .far = 100.0f
    });

    std::shared_ptr<gleam::CameraPerspective> perspective_camera_ =
    gleam::CameraPerspective::Create({
        .fov = 90.0f,
        .aspect = 1.0f,
        .near = 1.0f,
        .far = 100.0f
    });
};

#pragma endregion

#pragma region Contains Point

TEST_F(FrustumTest, ContainsPointWithOrthographicCamera) {
    const auto frustum = gleam::Frustum(orthographic_camera->projection_transform);

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
    const auto frustum = gleam::Frustum(perspective_camera_->projection_transform);

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

TEST_F(FrustumTest, IntersectsWithSphere) {
    const auto frustum = gleam::Frustum(perspective_camera_->projection_transform);

    auto sphere = gleam::Sphere {gleam::Vector3::Zero(), 0.5f};
    EXPECT_FALSE(frustum.IntersectsWithSphere(sphere));

    sphere.Translate(-0.5f);
    EXPECT_TRUE(frustum.IntersectsWithSphere(sphere));
}

TEST_F(FrustumTest, IntersectsWithBox3) {
    const auto frustum = gleam::Frustum(perspective_camera_->projection_transform);

    auto box = gleam::Box3 {gleam::Vector3::Zero(), 1.0f};
    EXPECT_FALSE(frustum.IntersectsWithBox3(box));

    box.Translate(-1.0f);
    EXPECT_TRUE(frustum.IntersectsWithBox3(box));
}

#pragma endregion