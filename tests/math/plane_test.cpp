// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gleam/math/plane.hpp>

#include <cmath>

#pragma region Constructors

TEST(Plane, DefaultConstructor) {
    const auto plane = gleam::Plane {};

    EXPECT_EQ(plane.normal, gleam::Vector3::Up());
    EXPECT_EQ(plane.distance, 0.0f);
}

TEST(Plane, ConstructorParameterized) {
    const auto plane = gleam::Plane {gleam::Vector3::Right(), 1.0f};

    EXPECT_EQ(plane.normal, gleam::Vector3::Right());
    EXPECT_EQ(plane.distance, 1.0f);
}

#pragma endregion

#pragma region Distance to Point

TEST(Plane, DistanceToPointOnPlane) {
    const auto plane = gleam::Plane {gleam::Vector3::Up(), 0.0f};
    const auto point = gleam::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 0.0f);
}

TEST(Plane, DistanceToPointAbovePlane) {
    const auto plane = gleam::Plane {gleam::Vector3::Up(), 0.0f};
    const auto point = gleam::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.0f);
}

TEST(Plane, DistanceToPointBelowPlane) {
    const auto plane = gleam::Plane {gleam::Vector3::Up(), 0.0f};
    const auto point = gleam::Vector3 {0.0f, -1.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), -1.0f);
}

TEST(Plane, DistanceToPointWithOffset) {
    auto plane = gleam::Plane {gleam::Vector3::Up(), 1.0f};
    auto point = gleam::Vector3 {0.0f, 2.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 3.0f);
}

TEST(Plane, DistanceToPointWithNegativeOffset) {
    auto plane = gleam::Plane {gleam::Vector3::Up(), -1.0f};
    auto point = gleam::Vector3 {0.0f, 2.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.0f);
}

TEST(Plane, DistanceToPointWithArbitraryNormal) {
    auto point = gleam::Vector3 {1.0f, 1.0f, 1.0f};
    auto plane = gleam::Plane {{0.577350259f}, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.7320508f);
}

TEST(Plane, DistanceToPointWithArbitraryNormalAndOffset) {
    auto point = gleam::Vector3 {1.0f, 1.0f, 1.0f};
    auto plane = gleam::Plane {{0.577350259f}, 0.577350259f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 2.30940104f);
}

TEST(Plane, DistanceToPointWithNonUnitNormalAndOffset) {
    auto point = gleam::Vector3 {1.0f, 1.0f, 1.0f};
    auto plane = gleam::Plane {{1.0f, 1.0f, 1.0f}, 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 4.0f);
}

#pragma endregion

#pragma region Distance to Sphere

TEST(Plane, DistanceToSphereWithCenterOnPlane) {
    auto plane = gleam::Plane {gleam::Vector3::Up(), 0.0f};
    auto sphere = gleam::Sphere {gleam::Vector3::Zero(), 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToSphere(sphere), -1.0f);
}

TEST(Plane, DistanceToSphereAbovePlane) {
    auto plane = gleam::Plane {gleam::Vector3::Up(), 1.0f};
    auto sphere = gleam::Sphere {gleam::Vector3 {0.0f, 3.0f, 0.0f}, 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToSphere(sphere), 3.0f);
}

#pragma endregion

#pragma region Normalize Plane

TEST(Plane, NormalizePlanWithNonUnitNormal) {
    auto plane = gleam::Plane {{2.0f, 0.0f, 0.0f}, 4.0f};
    plane.Normalize();

    EXPECT_VEC3_EQ(plane.normal, gleam::Vector3::Right());
    EXPECT_FLOAT_EQ(plane.distance, 2.0f);
}

TEST(Plane, NormalizePlaneWithUnitNormal) {
    auto plane = gleam::Plane {gleam::Vector3::Up(), 1.0f};
    plane.Normalize();

    EXPECT_VEC3_EQ(plane.normal, gleam::Vector3::Up());
    EXPECT_FLOAT_EQ(plane.distance, 1.0f);
}

#pragma endregion