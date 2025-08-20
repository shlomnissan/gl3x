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