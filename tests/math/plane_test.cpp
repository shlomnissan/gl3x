/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <vglx/math/plane.hpp>

#include <cassert>

#pragma region Constructors

TEST(Plane, DefaultConstructor) {
    constexpr auto plane = gl3x::Plane {};

    EXPECT_EQ(plane.normal, gl3x::Vector3::Up());
    EXPECT_EQ(plane.distance, 0.0f);

    static_assert(plane.normal == gl3x::Vector3::Up());
    static_assert(plane.distance == 0.0f);
}

TEST(Plane, ConstructorParameterized) {
    constexpr auto plane = gl3x::Plane {gl3x::Vector3::Right(), 1.0f};

    EXPECT_EQ(plane.normal, gl3x::Vector3::Right());
    EXPECT_EQ(plane.distance, 1.0f);

    static_assert(plane.normal == gl3x::Vector3::Right());
    static_assert(plane.distance == 1.0f);
}

#pragma endregion

#pragma region Distance to Point

TEST(Plane, DistanceToPointOnPlane) {
    constexpr auto plane = gl3x::Plane {gl3x::Vector3::Up(), 0.0f};
    constexpr auto point = gl3x::Vector3 {0.0f, 0.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 0.0f);

    static_assert(plane.DistanceToPoint(point) == 0.0f);
}

TEST(Plane, DistanceToPointAbovePlane) {
    constexpr auto plane = gl3x::Plane {gl3x::Vector3::Up(), 0.0f};
    constexpr auto point = gl3x::Vector3 {0.0f, 1.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.0f);

    static_assert(plane.DistanceToPoint(point) == 1.0f);
}

TEST(Plane, DistanceToPointBelowPlane) {
    constexpr const auto plane = gl3x::Plane {gl3x::Vector3::Up(), 0.0f};
    constexpr const auto point = gl3x::Vector3 {0.0f, -1.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), -1.0f);

    static_assert(plane.DistanceToPoint(point) == -1.0f);
}

TEST(Plane, DistanceToPointWithOffset) {
    constexpr auto plane = gl3x::Plane {gl3x::Vector3::Up(), 1.0f};
    constexpr auto point = gl3x::Vector3 {0.0f, 2.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 3.0f);

    static_assert(plane.DistanceToPoint(point) == 3.0f);
}

TEST(Plane, DistanceToPointWithNegativeOffset) {
    constexpr auto plane = gl3x::Plane {gl3x::Vector3::Up(), -1.0f};
    constexpr auto point = gl3x::Vector3 {0.0f, 2.0f, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.0f);

    static_assert(plane.DistanceToPoint(point) == 1.0f);
}

TEST(Plane, DistanceToPointWithArbitraryNormal) {
    constexpr auto point = gl3x::Vector3 {1.0f, 1.0f, 1.0f};
    constexpr auto plane = gl3x::Plane {{0.577350259f}, 0.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 1.7320508f);

    static_assert(plane.DistanceToPoint(point) == 1.7320508f);
}

TEST(Plane, DistanceToPointWithArbitraryNormalAndOffset) {
    constexpr auto point = gl3x::Vector3 {1.0f, 1.0f, 1.0f};
    constexpr auto plane = gl3x::Plane {{0.577350259f}, 0.577350259f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 2.30940104f);

    static_assert(plane.DistanceToPoint(point) == 2.30940104f);
}

TEST(Plane, DistanceToPointWithNonUnitNormalAndOffset) {
    constexpr auto point = gl3x::Vector3 {1.0f, 1.0f, 1.0f};
    constexpr auto plane = gl3x::Plane {{1.0f, 1.0f, 1.0f}, 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToPoint(point), 4.0f);

    static_assert(plane.DistanceToPoint(point) == 4.0f);
}

#pragma endregion

#pragma region Distance to Sphere

TEST(Plane, DistanceToSphereWithCenterOnPlane) {
    constexpr auto plane = gl3x::Plane {gl3x::Vector3::Up(), 0.0f};
    constexpr auto sphere = gl3x::Sphere {gl3x::Vector3::Zero(), 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToSphere(sphere), -1.0f);

    static_assert(plane.DistanceToSphere(sphere) == -1.0f);
}

TEST(Plane, DistanceToSphereAbovePlane) {
    constexpr auto plane = gl3x::Plane {gl3x::Vector3::Up(), 1.0f};
    constexpr auto sphere = gl3x::Sphere {gl3x::Vector3 {0.0f, 3.0f, 0.0f}, 1.0f};

    EXPECT_FLOAT_EQ(plane.DistanceToSphere(sphere), 3.0f);

    static_assert(plane.DistanceToSphere(sphere) == 3.0f);
}

#pragma endregion

#pragma region Normalize Plane

TEST(Plane, NormalizePlanWithNonUnitNormal) {
    auto p1 = gl3x::Plane {{2.0f, 0.0f, 0.0f}, 4.0f};
    p1.Normalize();

    EXPECT_VEC3_NEAR(p1.normal, gl3x::Vector3::Right(), 1e-4f);
    EXPECT_NEAR(p1.distance, 2.0f, 1e-4f);

    constexpr auto p2 = []() {
        auto p = gl3x::Plane {{2.0f, 0.0f, 0.0f}, 4.0f};
        p.Normalize();
        return p;
    }();

    static_assert(ApproxEqual(p2.normal.x, 1.0f));
    static_assert(ApproxEqual(p2.normal.y, 0.0f));
    static_assert(ApproxEqual(p2.normal.z, 0.0f));
    static_assert(ApproxEqual(p2.distance, 2.0f));
}

TEST(Plane, NormalizePlaneWithUnitNormal) {
    auto p1 = gl3x::Plane {gl3x::Vector3::Up(), 1.0f};
    p1.Normalize();

    EXPECT_VEC3_NEAR(p1.normal, gl3x::Vector3::Up(), 1e-4f);
    EXPECT_NEAR(p1.distance, 1.0f, 1e-4f);

    constexpr auto p2 = []() {
        auto p = gl3x::Plane {gl3x::Vector3::Up(), 1.0f};
        p.Normalize();
        return p;
    }();

    static_assert(ApproxEqual(p2.normal.x, 0.0f));
    static_assert(ApproxEqual(p2.normal.y, 1.0f));
    static_assert(ApproxEqual(p2.normal.z, 0.0f));
    static_assert(ApproxEqual(p2.distance, 1.0f));
}

#pragma endregion