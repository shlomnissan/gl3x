/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gl3x/math/frustum.hpp>
#include <gl3x/cameras/orthographic_camera.hpp>
#include <gl3x/cameras/perspective_camera.hpp>

#pragma region Fixtures

class FrustumTest : public ::testing::Test {
protected:
    static constexpr gl3x::Matrix4 perspective_projection = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.02020204f, -2.02020192f,
        0.0f, 0.0f, -1.0f, 0.0f
    };

    static constexpr gl3x::Matrix4 orthographic_projection = {
        1.0f,  0.0f, 0.0f, -0.0f,
        0.0f,  1.0f, 0.0f, 0.0f,
        0.0f,  0.0f, -0.0202020f, -1.02020204f,
       -0.0f, -0.0f, 0.0f, 1.0f
    };
};

#pragma endregion

#pragma region Contains Point

TEST_F(FrustumTest, ContainsPointWithOrthographicCamera) {
    constexpr auto frustum = gl3x::Frustum(orthographic_projection);

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

    static_assert(!frustum.ContainsPoint({-1.1f, -1.1f, -1.001f}));
    static_assert(!frustum.ContainsPoint({-1.1f, -1.1f, -100.1f}));
    static_assert(!frustum.ContainsPoint({0.0f, 0.0f, -101.0f}));
    static_assert(!frustum.ContainsPoint({0.0f, 0.0f, 0.0f}));
    static_assert(!frustum.ContainsPoint({1.1f, 1.1f, -1.001f}));
    static_assert(!frustum.ContainsPoint({1.1f, 1.1f, -100.1f}));
    static_assert(frustum.ContainsPoint({-1.0f, -1.0f, -1.001f}));
    static_assert(frustum.ContainsPoint({-1.0f, -1.0f, -100.0f}));
    static_assert(frustum.ContainsPoint({0.0f, 0.0f, -1.001f}));
    static_assert(frustum.ContainsPoint({0.0f, 0.0f, -100.0f}));
    static_assert(frustum.ContainsPoint({0.0f, 0.0f, -50.0f}));
    static_assert(frustum.ContainsPoint({1.0f, 1.0f, -1.001f}));
    static_assert(frustum.ContainsPoint({1.0f, 1.0f, -100.0f}));
}

TEST_F(FrustumTest, ContainsPointWithPerspectiveCamera) {
    constexpr auto frustum = gl3x::Frustum(perspective_projection);

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

    static_assert(!frustum.ContainsPoint({-1.1f, -1.1f, -1.001f}));
    static_assert(!frustum.ContainsPoint({-100.1f, -100.1f, -100.1f}));
    static_assert(!frustum.ContainsPoint({0.0f, 0.0f, -101.0f}));
    static_assert(!frustum.ContainsPoint({0.0f, 0.0f, 0.0f}));
    static_assert(!frustum.ContainsPoint({1.1f, 1.1f, -1.001f}));
    static_assert(!frustum.ContainsPoint({100.1f, 100.1f, -100.1f}));
    static_assert(frustum.ContainsPoint({-1.0f, -1.0f, -1.001f}));
    static_assert(frustum.ContainsPoint({-99.999f, -99.999f, -99.999f}));
    static_assert(frustum.ContainsPoint({0.0f, 0.0f, -1.001f}));
    static_assert(frustum.ContainsPoint({0.0f, 0.0f, -50.0f}));
    static_assert(frustum.ContainsPoint({0.0f, 0.0f, -99.999f}));
    static_assert(frustum.ContainsPoint({1.0f, 1.0f, -1.001f}));
    static_assert(frustum.ContainsPoint({99.999f, 99.999f, -99.999f}));
}

#pragma endregion

#pragma region Intersections

TEST_F(FrustumTest, IntersectsWithSphere) {
    constexpr auto frustum = gl3x::Frustum(perspective_projection);

    constexpr auto s1 = gl3x::Sphere {gl3x::Vector3::Zero(), 0.5f};
    EXPECT_FALSE(frustum.IntersectsWithSphere(s1));
    static_assert(!frustum.IntersectsWithSphere(s1));

    constexpr auto s2 = gl3x::Sphere {gl3x::Vector3 {-0.5f}, 0.5f};
    EXPECT_TRUE(frustum.IntersectsWithSphere(s2));
    static_assert(frustum.IntersectsWithSphere(s2));
}

TEST_F(FrustumTest, IntersectsWithBox3) {
    constexpr auto frustum = gl3x::Frustum(perspective_projection);

    constexpr auto b1 = gl3x::Box3 {gl3x::Vector3::Zero(), 1.0f};
    EXPECT_FALSE(frustum.IntersectsWithBox3(b1));
    static_assert(!frustum.IntersectsWithBox3(b1));

    constexpr auto b2 = gl3x::Box3 {gl3x::Vector3 {-1.0f}, 1.0f};
    EXPECT_TRUE(frustum.IntersectsWithBox3(b2));
    static_assert(frustum.IntersectsWithBox3(b2));
}

#pragma endregion