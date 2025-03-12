// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/plane.hpp>

#include <cmath>

#pragma region Constructors

TEST(Plane, DefaultConstructor) {
    const auto plane = engine::Plane {};

    EXPECT_EQ(plane.Normal(), engine::Vector3::Up());
    EXPECT_EQ(plane.Distance(), 0.0f);
}

TEST(Plane, ConstructorParameterized) {
    const auto plane = engine::Plane {engine::Vector3::Right(), 1.0f};

    EXPECT_EQ(plane.Normal(), engine::Vector3::Right());
    EXPECT_EQ(plane.Distance(), 1.0f);
}

#pragma endregion

#pragma region Distance to Point

TEST(Plane, DistanceToPointOnPlane) {
    const auto plane = engine::Plane {engine::Vector3::Up(), 0.0f};
    const auto point = engine::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 0.0f);
}

TEST(Plane, DistanceToPointAbovePlane) {
    const auto plane = engine::Plane {engine::Vector3::Up(), 0.0f};
    const auto point = engine::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.0f);
}

TEST(Plane, DistanceToPointBelowPlane) {
    const auto plane = engine::Plane {engine::Vector3::Up(), 0.0f};
    const auto point = engine::Vector3 {0.0f, -1.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), -1.0f);
}

TEST(Plane, DistanceToPointWithOffset) {
    auto plane = engine::Plane {engine::Vector3::Up(), 1.0f};
    auto point = engine::Vector3 {0.0f, 2.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.0f);
}

TEST(Plane, DistanceToPointWithNegativeOffset) {
    auto plane = engine::Plane {engine::Vector3::Up(), -1.0f};
    auto point = engine::Vector3 {0.0f, 2.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 3.0f);
}

TEST(Plane, DistanceToPointWithArbitraryNormal) {
    auto plane = engine::Plane {Normalize(engine::Vector3 {1.0f, 1.0f, 1.0f}), 0.0f};
    auto point = engine::Vector3 {1.0f, 1.0f, 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), std::sqrt(3.0f));
}

TEST(Plane, DistanceToPointWithArbitraryNormalAndOffset) {
    auto plane = engine::Plane {Normalize(engine::Vector3 {1.0f, 1.0f, 1.0f}), 1.0f};
    auto point = engine::Vector3 {1.0f, 1.0f, 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), std::sqrt(3.0f) - 1.0f);
}

#pragma endregion

#pragma region Distance to Sphere

TEST(Plane, DistanceToSphereWithCenterOnPlane) {
    auto plane = engine::Plane {engine::Vector3::Up(), 0.0f};
    auto sphere = engine::Sphere {engine::Vector3::Zero(), 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToSphere(sphere), -1.0f);
}

TEST(Plane, DistanceToSphereAbovePlane) {
    auto plane = engine::Plane {engine::Vector3::Up(), 1.0f};
    auto sphere = engine::Sphere {engine::Vector3 {0.0f, 3.0f, 0.0f}, 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToSphere(sphere), 1.0f);
}

#pragma endregion

#pragma region Normalize Plane

TEST(Plane, NormalizePlanWithNonUnitNormal) {
    auto plane = engine::Plane {{2.0f, 0.0f, 0.0f}, 4.0f};
    plane.Normalize();

    EXPECT_VEC3_EQ(plane.Normal(), engine::Vector3::Right());
    EXPECT_FLOAT_EQ(plane.Distance(), 2.0f);
}

TEST(Plane, NormalizePlaneWithUnitNormal) {
    auto plane = engine::Plane {engine::Vector3::Up(), 1.0f};
    plane.Normalize();

    EXPECT_VEC3_EQ(plane.Normal(), engine::Vector3::Up());
    EXPECT_FLOAT_EQ(plane.Distance(), 1.0f);
}

#pragma endregion