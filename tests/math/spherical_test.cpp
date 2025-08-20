/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gleam/math/spherical.hpp>
#include <gleam/math/utilities.hpp>

#include <cassert>

#pragma region Constructors

TEST(Sphere, DefaultConstructor) {
    constexpr auto phi = gleam::math::DegToRad(45.0f);
    constexpr auto theta = gleam::math::DegToRad(90.0f);
    constexpr auto s = gleam::Spherical {2.5f, phi, theta};

    EXPECT_FLOAT_EQ(s.radius, 2.5f);
    EXPECT_FLOAT_EQ(s.phi, gleam::math::DegToRad(45.0f));
    EXPECT_FLOAT_EQ(s.theta, gleam::math::DegToRad(90.0f));

    static_assert(s.radius == 2.5f);
    static_assert(s.phi == gleam::math::DegToRad(45.0f));
    static_assert(s.theta == gleam::math::DegToRad(90.0f));
}

#pragma endregion

#pragma region MakeSafe

TEST(Spherical, MakeSafeClampsLowerBound) {
    constexpr auto phi = -gleam::math::DegToRad(10.0f);
    constexpr auto theta = gleam::math::DegToRad(30.0f);

    auto s = gleam::Spherical {2.0f, phi, theta};
    s.MakeSafe();

    EXPECT_FLOAT_EQ(s.phi, gleam::math::eps);
    EXPECT_FLOAT_EQ(s.radius, 2.0f);
    EXPECT_FLOAT_EQ(s.theta, gleam::math::DegToRad(30.0f));

    static_assert([&]{
        auto s = gleam::Spherical {2.0f, phi, theta};
        s.MakeSafe();
        return s.phi == gleam::math::eps;
    }());
}

TEST(Spherical, MakeSafeClampsUpperBound) {
    constexpr auto phi = gleam::math::pi + gleam::math::DegToRad(1.0f);
    constexpr auto theta = gleam::math::DegToRad(30.0f);

    auto s = gleam::Spherical {2.0f, phi, theta};
    s.MakeSafe();

    EXPECT_FLOAT_EQ(s.phi, gleam::math::pi - gleam::math::eps);
    EXPECT_FLOAT_EQ(s.radius, 2.0f);
    EXPECT_FLOAT_EQ(s.theta, gleam::math::DegToRad(30.0f));

    static_assert([&]{
        auto s = gleam::Spherical {2.0f, phi, theta};
        s.MakeSafe();
        return s.phi == gleam::math::pi - gleam::math::eps;
    }());
}

TEST(Spherical, MakeSafeNoChangeWhenInRange) {
    constexpr auto phi = gleam::math::pi_over_2;
    constexpr auto theta = gleam::math::DegToRad(30.0f);

    auto s = gleam::Spherical {2.0f, phi, theta};
    s.MakeSafe();

    EXPECT_FLOAT_EQ(s.phi, gleam::math::pi_over_2);
    EXPECT_FLOAT_EQ(s.radius, 2.0f);
    EXPECT_FLOAT_EQ(s.theta, gleam::math::DegToRad(30.0f));

    static_assert([&]{
        auto s = gleam::Spherical {2.0f, phi, theta};
        s.MakeSafe();
        return s.phi == gleam::math::pi_over_2;
    }());
}

#pragma endregion

#pragma region ToVector3

TEST(Spherical, ToVector3Basic) {
    constexpr auto phi = gleam::math::pi_over_4; // 45° from "up"
    constexpr auto theta = gleam::math::pi_over_4; // 45° azimuth
    constexpr auto s = gleam::Spherical {1.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    constexpr auto expect_x = gleam::math::Sin(phi) * gleam::math::Cos(theta);
    constexpr auto expect_y = gleam::math::Cos(phi);
    constexpr auto expect_z = gleam::math::Sin(phi) * gleam::math::Sin(theta);

    EXPECT_VEC3_EQ(v, {expect_x, expect_y, expect_z});

    static_assert(v.x == expect_x);
    static_assert(v.y == expect_y);
    static_assert(v.z == expect_z);
}

TEST(Spherical, ToVector3UpPoleIgnoresTheta) {
    // Any theta should yield the same result when phi = 0.0f (pointing straight "up")
    constexpr auto phi = 0.0f;
    constexpr auto theta = gleam::math::pi_over_4;
    constexpr auto s = gleam::Spherical {3.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    EXPECT_VEC3_EQ(v, {0.0f, 3.0f, 0.0f});

    static_assert(v.x == 0.0f);
    static_assert(v.y == 3.0f);
    static_assert(v.z == 0.0f);
}

TEST(Spherical, ToVector3EquatorXDirection) {
    // On the equator (phi = π/2) with theta = 0 should point along +X
    constexpr auto phi = gleam::math::pi_over_2;
    constexpr auto theta = 0.0f;
    constexpr auto s = gleam::Spherical {3.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    EXPECT_VEC3_EQ(v, {3.0f, 0.0f, 0.0f});

    static_assert(v.x == 3.0f);
    static_assert(v.y == 0.0f);
    static_assert(v.z == 0.0f);
}

TEST(Spherical, ToVector3EquatorZDirection) {
    // On the equator (phi = π/2) with theta = π/2 should point along +Z
    constexpr auto phi = gleam::math::pi_over_2;
    constexpr auto theta = gleam::math::pi_over_2;
    constexpr auto s = gleam::Spherical {3.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    EXPECT_VEC3_EQ(v, {0.0f, 0.0f, 3.0f});

    static_assert(v.x == 0.0f);
    static_assert(v.y == 0.0f);
    static_assert(v.z == 3.0f);
}

#pragma endregion