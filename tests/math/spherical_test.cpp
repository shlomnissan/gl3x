/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <vglx/math/spherical.hpp>
#include <vglx/math/utilities.hpp>

#include <cassert>

#pragma region Constructors

TEST(Sphere, DefaultConstructor) {
    constexpr auto phi = vglx::math::DegToRad(45.0f);
    constexpr auto theta = vglx::math::DegToRad(90.0f);
    constexpr auto s = vglx::Spherical {2.5f, phi, theta};

    EXPECT_FLOAT_EQ(s.radius, 2.5f);
    EXPECT_FLOAT_EQ(s.phi, vglx::math::DegToRad(45.0f));
    EXPECT_FLOAT_EQ(s.theta, vglx::math::DegToRad(90.0f));

    static_assert(s.radius == 2.5f);
    static_assert(s.phi == vglx::math::DegToRad(45.0f));
    static_assert(s.theta == vglx::math::DegToRad(90.0f));
}

#pragma endregion

#pragma region MakeSafe

TEST(Spherical, MakeSafeClampsLowerBound) {
    constexpr auto phi = vglx::math::DegToRad(30.0f);
    constexpr auto theta = vglx::math::pi_over_2 + vglx::math::eps;

    auto s = vglx::Spherical {2.0f, phi, theta};
    s.MakeSafe();

    constexpr auto expected = vglx::math::pi_over_2 - vglx::math::eps;

    EXPECT_FLOAT_EQ(s.phi, vglx::math::DegToRad(30.0f));
    EXPECT_FLOAT_EQ(s.theta, expected);
    EXPECT_FLOAT_EQ(s.radius, 2.0f);

    static_assert([&]{
        auto s = vglx::Spherical {2.0f, phi, theta};
        s.MakeSafe();
        return s.theta == expected;
    }());
}

TEST(Spherical, MakeSafeClampsUpperBound) {
    constexpr auto phi = vglx::math::DegToRad(30.0f);
    constexpr auto theta = -vglx::math::pi_over_2 - vglx::math::eps;

    auto s = vglx::Spherical {2.0f, phi, theta};
    s.MakeSafe();

    constexpr auto expected = -vglx::math::pi_over_2 + vglx::math::eps;

    EXPECT_FLOAT_EQ(s.phi, vglx::math::DegToRad(30.0f));
    EXPECT_FLOAT_EQ(s.theta, expected);
    EXPECT_FLOAT_EQ(s.radius, 2.0f);

    static_assert([&]{
        auto s = vglx::Spherical {2.0f, phi, theta};
        s.MakeSafe();
        return s.theta == expected;
    }());
}

TEST(Spherical, MakeSafeNoChangeWhenInRange) {
    constexpr auto phi = vglx::math::DegToRad(30.0f);
    constexpr auto theta = vglx::math::DegToRad(30.0f);

    auto s = vglx::Spherical {2.0f, phi, theta};
    s.MakeSafe();

    EXPECT_FLOAT_EQ(s.phi, vglx::math::DegToRad(30.0f));
    EXPECT_FLOAT_EQ(s.theta, vglx::math::DegToRad(30.0f));
    EXPECT_FLOAT_EQ(s.radius, 2.0f);

    static_assert([&]{
        auto s = vglx::Spherical {2.0f, phi, theta};
        s.MakeSafe();
        return s.theta == vglx::math::DegToRad(30.0f);
    }());
}

#pragma endregion

#pragma region ToVector3

TEST(Spherical, ToVector3Basic) {
    constexpr auto phi = vglx::math::pi_over_4;
    constexpr auto theta = vglx::math::pi_over_4;
    constexpr auto s = vglx::Spherical {1.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    constexpr auto expect_x = vglx::math::Sin(phi) * vglx::math::Cos(theta);
    constexpr auto expect_y = vglx::math::Sin(theta);
    constexpr auto expect_z = vglx::math::Cos(phi) * vglx::math::Cos(theta);

    EXPECT_VEC3_EQ(v, {expect_x, expect_y, expect_z});

    static_assert(v.x == expect_x);
    static_assert(v.y == expect_y);
    static_assert(v.z == expect_z);
}

TEST(Spherical, ToVector3NorthPoleIgnoresPhi) {
    // At the north pole (theta = +π/2), phi has no effect.
    constexpr auto phi = vglx::math::pi_over_4;
    constexpr auto theta = vglx::math::pi_over_2; // north pole
    constexpr auto s = vglx::Spherical {3.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    EXPECT_VEC3_EQ(v, {0.0f, 3.0f, 0.0f});

    static_assert(v.x == 0.0f);
    static_assert(v.y == 3.0f);
    static_assert(v.z == 0.0f);
}

TEST(Spherical, ToVector3EquatorXDirection) {
    // On the equator (theta = 0) with phi = π/2 → +X
    constexpr auto phi = vglx::math::pi_over_2;
    constexpr auto theta = 0.0f;
    constexpr auto s = vglx::Spherical {3.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    EXPECT_VEC3_EQ(v, {3.0f, 0.0f, 0.0f});

    static_assert(v.x == 3.0f);
    static_assert(v.y == 0.0f);
    static_assert(v.z == 0.0f);
}

TEST(Spherical, ToVector3EquatorZDirection) {
    // On the equator (theta = 0) with phi = 0 → +Z.
    constexpr auto phi = 0.0f;
    constexpr auto theta = 0.0f;
    constexpr auto s = vglx::Spherical {3.0f, phi, theta};
    constexpr auto v = s.ToVector3();

    EXPECT_VEC3_EQ(v, {0.0f, 0.0f, 3.0f});

    static_assert(v.x == 0.0f);
    static_assert(v.y == 0.0f);
    static_assert(v.z == 3.0f);
}

#pragma endregion