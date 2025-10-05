/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>

#include "test_helpers.hpp"

#include <cassert>
#include <regex>

#include <gl3x/math/utilities.hpp>

using namespace gl3x;

#pragma region Degrees and Radians

TEST(MathUtilities, DegToRad) {
    static_assert(math::DegToRad(0.0f) == 0.0f);
    static_assert(math::DegToRad(90.0f) == math::pi / 2.0f);
    static_assert(math::DegToRad(180.0f) == math::pi);
    static_assert(math::DegToRad(360.0f) == math::two_pi);
    static_assert(math::DegToRad(45.0f) == math::pi / 4.0f);

    EXPECT_FLOAT_EQ(math::DegToRad(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::DegToRad(90.0f), math::pi / 2.0f);
    EXPECT_FLOAT_EQ(math::DegToRad(180.0f), math::pi);
    EXPECT_FLOAT_EQ(math::DegToRad(360.0f), math::two_pi);
    EXPECT_FLOAT_EQ(math::DegToRad(45.0f), math::pi / 4.0f);
}

TEST(MathUtilities, RadToDeg) {
    static_assert(math::RadToDeg(0.0f) == 0.0f);
    static_assert(math::RadToDeg(math::pi / 2.0f) == 90.0f);
    static_assert(math::RadToDeg(math::pi) == 180.0f);
    static_assert(math::RadToDeg(math::two_pi) == 360.0f);
    static_assert(math::RadToDeg(math::pi / 4.0f) == 45.0f);

    EXPECT_FLOAT_EQ(math::RadToDeg(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::pi / 2.0f), 90.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::pi), 180.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::two_pi), 360.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::pi / 4.0f), 45.0f);
}

#pragma endregion

#pragma region Sqrt

TEST(MathUtilities, SqrtAccuracyCommonCases) {
    EXPECT_NEAR(math::Sqrt(0.0f), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Sqrt(1.0f), 1.0f, 1e-4f);
    EXPECT_NEAR(math::Sqrt(2.0f), 1.4142f, 1e-4f);
    EXPECT_NEAR(math::Sqrt(4.0f), 2.0f, 1e-4f);
    EXPECT_NEAR(math::Sqrt(9.0f), 3.0f, 1e-4f);
    EXPECT_NEAR(math::Sqrt(16.0f), 4.0f, 1e-4f);
    EXPECT_NEAR(math::Sqrt(100.0f), 10.0f, 1e-3f);

    static_assert(ApproxEqual(math::Sqrt(1.0f), 1.0f));
    static_assert(ApproxEqual(math::Sqrt(0.0f), 0.0f));
    static_assert(math::Sqrt(4.0f) > 1.9f && math::Sqrt(4.0f) < 2.1f);
    static_assert(math::Sqrt(9.0f) > 2.9f && math::Sqrt(9.0f) < 3.1f);
}

TEST(MathUtilities, SqrtTinyValues) {
    EXPECT_NEAR(math::Sqrt(1e-10f), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Sqrt(std::numeric_limits<float>::min()), 0.0f, 1e-4f);

    static_assert(ApproxEqual(math::Sqrt(1e-10f), 0.0f));
    static_assert(ApproxEqual(math::Sqrt(std::numeric_limits<float>::min()), 0.0f));
}

TEST(MathUtilities, SqrtNegativeInputBehavior) {
    EXPECT_EQ(math::Sqrt(-1.0f), 0.0f);

    static_assert(math::Sqrt(-1.0f) == 0.0f);
}

TEST(MathUtilities, InverseSqrtAccuracyCommonCases) {
    EXPECT_NEAR(math::InverseSqrt(1.0f), 1.0f, 1e-4f);
    EXPECT_NEAR(math::InverseSqrt(4.0f), 0.5f, 1e-4f);
    EXPECT_NEAR(math::InverseSqrt(9.0f), 1.0f / 3.0f, 1e-4f);
    EXPECT_NEAR(math::InverseSqrt(16.0f), 0.25f, 1e-4f);
    EXPECT_NEAR(math::InverseSqrt(100.0f), 0.1f, 1e-3f);

    static_assert(ApproxEqual(math::InverseSqrt(1.0f), 1.0f));
    static_assert(math::InverseSqrt(4.0f) > 0.49f && math::InverseSqrt(4.0f) < 0.51f);
    static_assert(math::InverseSqrt(9.0f) > 0.32f && math::InverseSqrt(9.0f) < 0.35f);
}

TEST(MathUtilities, InverseSqrtTinyValues) {
    EXPECT_TRUE(std::isinf(math::InverseSqrt(0.0f)));
    EXPECT_GT(math::InverseSqrt(std::numeric_limits<float>::min()), 1e-18f);
    EXPECT_GT(math::InverseSqrt(1e-10f), 1e4f);

    static_assert(math::InverseSqrt(0.0f) == std::numeric_limits<float>::infinity());
    static_assert(math::InverseSqrt(std::numeric_limits<float>::min()) > 1e-18f);
    static_assert(math::InverseSqrt(1e-10f) > 1e-4f);
}

TEST(MathUtilities, InverseSqrtNegativeInputBehavior) {
    EXPECT_TRUE(std::isinf(math::InverseSqrt(-1.0f)));

    static_assert(math::InverseSqrt(-1.0f) == std::numeric_limits<float>::infinity());
}

#pragma endregion

#pragma region Cos

TEST(MathUtilities, CosCommonAngles) {
    EXPECT_NEAR(math::Cos(0.0f), 1.0f, 1e-4f);
    EXPECT_NEAR(math::Cos(math::pi_over_2), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Cos(math::pi), -1.0f, 1e-4f);
    EXPECT_NEAR(math::Cos(3.0f * math::pi_over_2), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Cos(math::two_pi), 1.0f, 1e-4f);

    static_assert(ApproxEqual(math::Cos(0.0f), 1.0f));
    static_assert(ApproxEqual(math::Cos(math::pi_over_2), 0.0f));
    static_assert(ApproxEqual(math::Cos(math::pi), -1.0f));
    static_assert(ApproxEqual(math::Cos(3.0f * math::pi_over_2), 0.0f));
    static_assert(ApproxEqual(math::Cos(math::two_pi), 1.0f));
}

TEST(MathUtilities, CosNegativeAngles) {
    EXPECT_NEAR(math::Cos(-math::pi_over_2), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Cos(-math::pi), -1.0f, 1e-4f);
    EXPECT_NEAR(math::Cos(-math::two_pi), 1.0f, 1e-4f);

    static_assert(ApproxEqual(math::Cos(-math::pi_over_2), 0.0f));
    static_assert(ApproxEqual(math::Cos(-math::pi), -1.0f));
    static_assert(ApproxEqual(math::Cos(-math::two_pi), 1.0f));
}

TEST(MathUtilities, CosSymmetryProperties) {
    constexpr float x = math::pi / 3.0f;
    EXPECT_NEAR(math::Cos(x), math::Cos(-x), 1e-4f);
    EXPECT_NEAR(math::Cos(math::pi - x), -math::Cos(x), 1e-4f);
    EXPECT_NEAR(math::Cos(math::pi + x), -math::Cos(x), 1e-4f);
    EXPECT_NEAR(math::Cos(math::two_pi - x), math::Cos(x), 1e-4f);

    static_assert(ApproxEqual(math::Cos(x), math::Cos(-x)));
    static_assert(ApproxEqual(math::Cos(math::pi - x), -math::Cos(x)));
    static_assert(ApproxEqual(math::Cos(math::pi + x), -math::Cos(x)));
    static_assert(ApproxEqual(math::Cos(math::two_pi - x), math::Cos(x)));
}

TEST(MathUtilities, CosPeriodicity) {
    constexpr float x = 1.23f;
    EXPECT_NEAR(math::Cos(x), math::Cos(x + math::two_pi), 1e-4f);
    EXPECT_NEAR(math::Cos(x), math::Cos(x - math::two_pi), 1e-4f);

    static_assert(ApproxEqual(math::Cos(x), math::Cos(x + math::two_pi)));
    static_assert(ApproxEqual(math::Cos(x), math::Cos(x - math::two_pi)));
}

#pragma endregion

#pragma region Sin

TEST(MathUtilities, SinCommonAngles) {
    EXPECT_NEAR(math::Sin(0.0f), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Sin(math::pi_over_2), 1.0f, 1e-4f);
    EXPECT_NEAR(math::Sin(math::pi), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Sin(3.0f * math::pi_over_2), -1.0f, 1e-4f);
    EXPECT_NEAR(math::Sin(math::two_pi), 0.0f, 1e-4f);

    static_assert(ApproxEqual(math::Sin(0.0f), 0.0f));
    static_assert(ApproxEqual(math::Sin(math::pi_over_2), 1.0f));
    static_assert(ApproxEqual(math::Sin(math::pi), 0.0f));
    static_assert(ApproxEqual(math::Sin(3.0f * math::pi_over_2), -1.0f));
    static_assert(ApproxEqual(math::Sin(math::two_pi), 0.0f));
}

TEST(MathUtilities, SinNegativeAngles) {
    EXPECT_NEAR(math::Sin(-math::pi_over_2), -1.0f, 1e-4f);
    EXPECT_NEAR(math::Sin(-math::pi), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Sin(-math::two_pi), 0.0f, 1e-4f);

    static_assert(ApproxEqual(math::Sin(-math::pi_over_2), -1.0f));
    static_assert(ApproxEqual(math::Sin(-math::pi), 0.0f));
    static_assert(ApproxEqual(math::Sin(-math::two_pi), 0.0f));
}

TEST(MathUtilities, SinSymmetryProperties) {
    constexpr float x = math::pi / 3.0f;
    EXPECT_NEAR(math::Sin(x), -math::Sin(-x), 1e-4f);
    EXPECT_NEAR(math::Sin(math::pi - x), math::Sin(x), 1e-4f);
    EXPECT_NEAR(math::Sin(math::pi + x), -math::Sin(x), 1e-4f);
    EXPECT_NEAR(math::Sin(math::two_pi - x), -math::Sin(x), 1e-4f);

    static_assert(ApproxEqual(math::Sin(x), -math::Sin(-x)));
    static_assert(ApproxEqual(math::Sin(math::pi - x), math::Sin(x)));
    static_assert(ApproxEqual(math::Sin(math::pi + x), -math::Sin(x)));
    static_assert(ApproxEqual(math::Sin(math::two_pi - x), -math::Sin(x)));
}

TEST(MathUtilities, SinPeriodicity) {
    constexpr float x = 1.23f;
    EXPECT_NEAR(math::Sin(x), math::Sin(x + math::two_pi), 1e-4f);
    EXPECT_NEAR(math::Sin(x), math::Sin(x - math::two_pi), 1e-4f);

    static_assert(ApproxEqual(math::Sin(x), math::Sin(x + math::two_pi)));
    static_assert(ApproxEqual(math::Sin(x), math::Sin(x - math::two_pi), 1e-3f));
}

#pragma endregion

#pragma region Lerp

TEST(MathUtilities, LerpBasic) {
    static_assert(math::Lerp(0.0f, 1.0f, 0.5f) == 0.5f);
    static_assert(math::Lerp(0.0f, 1.0f, 0.0f) == 0.0f);
    static_assert(math::Lerp(0.0f, 1.0f, 1.0f) == 1.0f);

    EXPECT_FLOAT_EQ(math::Lerp(0.0f, 1.0f, 0.5f), 0.5f);
    EXPECT_FLOAT_EQ(math::Lerp(0.0f, 1.0f, 0.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::Lerp(0.0f, 1.0f, 1.0f), 1.0f);
}

TEST(MathUtilities, LerpNegativeValues) {
    static_assert(math::Lerp(-1.0f, 1.0f, 0.5f) == 0.0f);
    static_assert(math::Lerp(-1.0f, -2.0f, 0.5f) == -1.5f);

    EXPECT_FLOAT_EQ(math::Lerp(-1.0f, 1.0f, 0.5f), 0.0f);
    EXPECT_FLOAT_EQ(math::Lerp(-1.0f, -2.0f, 0.5f), -1.5f);
}

TEST(MathUtilities, LerpOutOfRangeFactor) {
    static_assert(math::Lerp(0.0f, 1.0f, -0.5f) == -0.5f);
    static_assert(math::Lerp(0.0f, 1.0f, 1.5f) == 1.5f);

    EXPECT_FLOAT_EQ(math::Lerp(0.0f, 1.0f, -0.5f), -0.5f);
    EXPECT_FLOAT_EQ(math::Lerp(0.0f, 1.0f, 1.5f), 1.5f);
}

#pragma endregion

#pragma region Atan

TEST(MathUtilities, AtanCommonAngles) {
    EXPECT_NEAR(math::Atan(0.0f), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Atan(1.0f), math::pi_over_4, 1e-4f);
    EXPECT_NEAR(math::Atan(-1.0f), -math::pi_over_4, 1e-4f);
    EXPECT_NEAR(math::Atan(std::numeric_limits<float>::infinity()), math::pi_over_2, 1e-4f);
    EXPECT_NEAR(math::Atan(-std::numeric_limits<float>::infinity()), -math::pi_over_2, 1e-4f);

    static_assert(ApproxEqual(math::Atan(0.0f), 0.0f));
    static_assert(ApproxEqual(math::Atan(1.0f), math::pi_over_4));
    static_assert(ApproxEqual(math::Atan(-1.0f), -math::pi_over_4));
}

TEST(MathUtilities, AtanSymmetryProperties) {
    constexpr float x = 0.75f;
    EXPECT_NEAR(math::Atan(x), -math::Atan(-x), 1e-4f);

    static_assert(ApproxEqual(math::Atan(x), -math::Atan(-x)));
}

TEST(MathUtilities, AtanLimits) {
    EXPECT_NEAR(math::Atan(1e6f), math::pi_over_2, 1e-4f);
    EXPECT_NEAR(math::Atan(-1e6f), -math::pi_over_2, 1e-4f);
}

TEST(MathUtilities, AtanMonotonicity) {
    constexpr float a = 0.5f;
    constexpr float b = 1.0f;
    constexpr float c = 2.0f;

    EXPECT_GT(math::Atan(b), math::Atan(a));
    EXPECT_GT(math::Atan(c), math::Atan(b));
    EXPECT_GT(math::Atan(a), math::Atan(-a));
}

#pragma endregion

#pragma region Atan2

TEST(MathUtilities, Atan2CommonAngles) {
    EXPECT_NEAR(math::Atan2(0.0f, 1.0f), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Atan2(1.0f, 0.0f), math::pi_over_2, 1e-4f);
    EXPECT_NEAR(math::Atan2(0.0f, -1.0f), math::pi, 1e-4f);
    EXPECT_NEAR(math::Atan2(-1.0f, 0.0f), -math::pi_over_2, 1e-4f);
    EXPECT_NEAR(math::Atan2(1.0f, 1.0f), math::pi_over_4, 1e-4f);
    EXPECT_NEAR(math::Atan2(-1.0f, -1.0f), -3.0f * math::pi_over_4, 1e-4f);

    static_assert(ApproxEqual(math::Atan2(0.0f, 1.0f), 0.0f));
    static_assert(ApproxEqual(math::Atan2(1.0f, 0.0f), math::pi_over_2));
    static_assert(ApproxEqual(math::Atan2(0.0f, -1.0f), math::pi));
    static_assert(ApproxEqual(math::Atan2(-1.0f, 0.0f), -math::pi_over_2));
    static_assert(ApproxEqual(math::Atan2(1.0f, 1.0f), math::pi_over_4));
}

TEST(MathUtilities, Atan2SymmetryProperties) {
    constexpr float x = 0.75f;
    constexpr float y = 0.5f;

    EXPECT_NEAR(math::Atan2(y, x), -math::Atan2(-y, x), 1e-4f);
    static_assert(ApproxEqual(math::Atan2(y, x), -math::Atan2(-y, x)));
}

TEST(MathUtilities, Atan2DiagonalQuadrants) {
    EXPECT_NEAR(math::Atan2(1.0f, -1.0f), 3.0f * math::pi_over_4, 1e-4f);
    EXPECT_NEAR(math::Atan2(-1.0f, -1.0f), -3.0f * math::pi_over_4, 1e-4f);
    EXPECT_NEAR(math::Atan2(-1.0f, 1.0f), -math::pi_over_4, 1e-4f);

    static_assert(ApproxEqual(math::Atan2(1.0f, -1.0f), 3.0f * math::pi_over_4));
    static_assert(ApproxEqual(math::Atan2(-1.0f, -1.0f), -3.0f * math::pi_over_4));
    static_assert(ApproxEqual(math::Atan2(-1.0f, 1.0f), -math::pi_over_4));
}

TEST(MathUtilities, Atan2ZeroZeroReturnsZero) {
    EXPECT_NEAR(math::Atan2(0.0f, 0.0f), 0.0f, 1e-4f); // defined fallback
    static_assert(ApproxEqual(math::Atan2(0.0f, 0.0f), 0.0f));
}

#pragma endregion

#pragma region Asin

TEST(MathUtilities, AsinCommonAngles) {
    EXPECT_NEAR(math::Asin(0.0f), 0.0f, 1e-4f);
    EXPECT_NEAR(math::Asin(0.5f), math::pi_over_6, 1e-4f);
    EXPECT_NEAR(math::Asin(0.70710678f), math::pi_over_4, 1e-4f); // sin(π/4)
    EXPECT_NEAR(math::Asin(1.0f), math::pi_over_2, 1e-4f);
    EXPECT_NEAR(math::Asin(-0.5f), -math::pi_over_6, 1e-4f);
    EXPECT_NEAR(math::Asin(-1.0f), -math::pi_over_2, 1e-4f);

    static_assert(ApproxEqual(math::Asin(0.0f), 0.0f));
    static_assert(ApproxEqual(math::Asin(0.5f), math::pi_over_6));
    static_assert(ApproxEqual(math::Asin(1.0f), math::pi_over_2));
    static_assert(ApproxEqual(math::Asin(-0.5f), -math::pi_over_6));
    static_assert(ApproxEqual(math::Asin(-1.0f), -math::pi_over_2));
}

TEST(MathUtilities, AsinSymmetryProperties) {
    constexpr float x = 0.6f;

    EXPECT_NEAR(math::Asin(-x), -math::Asin(x), 1e-4f);
    static_assert(ApproxEqual(math::Asin(-x), -math::Asin(x)));
}

TEST(MathUtilities, AsinInverseProperty) {
    constexpr float x = 0.5f;
    const auto angle = math::Asin(x);
    EXPECT_NEAR(math::Sin(angle), x, 1e-4f);

    constexpr float y = -0.7f;
    const auto angle2 = math::Asin(y);
    EXPECT_NEAR(math::Sin(angle2), y, 1e-4f);
}

#pragma endregion

#pragma region Cantor Pairing

TEST(MathUtilities, CantorPairingZeroPairing) {
    static_assert(math::CantorPairing(0, 0) == 0);
    static_assert(math::CantorPairing(0, 1) == 2);
    static_assert(math::CantorPairing(1, 0) == 1);

    EXPECT_EQ(math::CantorPairing(0, 0), 0);
    EXPECT_EQ(math::CantorPairing(0, 1), 2);
    EXPECT_EQ(math::CantorPairing(1, 0), 1);
}

TEST(MathUtilities, CantorPairingKnownValues) {
    static_assert(math::CantorPairing(2, 3) == 18);
    static_assert(math::CantorPairing(3, 2) == 17);
    static_assert(math::CantorPairing(5, 10) == 130);
    static_assert(math::CantorPairing(10, 5) == 125);

    EXPECT_EQ(math::CantorPairing(2, 3), 18);
    EXPECT_EQ(math::CantorPairing(3, 2), 17);
    EXPECT_EQ(math::CantorPairing(5, 10), 130);
    EXPECT_EQ(math::CantorPairing(10, 5), 125);
}

TEST(MathUtilitieTest, CantorPairingUnorderedSymmetry) {
    static_assert(math::CantorPairingUnordered(2, 3) == math::CantorPairingUnordered(3, 2));
    static_assert(math::CantorPairingUnordered(10, 5) == math::CantorPairingUnordered(5, 10));

    EXPECT_EQ(math::CantorPairingUnordered(2, 3), math::CantorPairingUnordered(3, 2));
    EXPECT_EQ(math::CantorPairingUnordered(10, 5), math::CantorPairingUnordered(5, 10));
}

TEST(MathUtilitieTest, CantorPairingUnorderedDistinctFromOrdered) {
    static_assert(math::CantorPairingUnordered(2, 3) == math::CantorPairing(2, 3));
    static_assert(math::CantorPairingUnordered(2, 3) != math::CantorPairing(3, 2));

    EXPECT_EQ(math::CantorPairingUnordered(2, 3), math::CantorPairing(2, 3));
    EXPECT_NE(math::CantorPairingUnordered(2, 3), math::CantorPairing(3, 2));
}

#pragma endregion

#pragma region Clamp

TEST(MathUtilities, ClampBasicBehavior) {
    static_assert(math::Clamp(-1.0f, 0.0f, 1.0f) == 0.0f);
    static_assert(math::Clamp(0.5f, 0.0f, 1.0f) == 0.5f);
    static_assert(math::Clamp(2.0f, 0.0f, 1.0f) == 1.0f);

    EXPECT_FLOAT_EQ(math::Clamp(-1.0f, 0.0f, 1.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::Clamp(0.5f, 0.0f, 1.0f), 0.5f);
    EXPECT_FLOAT_EQ(math::Clamp(2.0f, 0.0f, 1.0f), 1.0f);
}

TEST(MathUtilities, ClampDegenerateRangeReturnsBound) {
    static_assert(math::Clamp(-5.0f, 2.0f, 2.0f) == 2.0f);
    static_assert(math::Clamp( 2.0f, 2.0f, 2.0f) == 2.0f);
    static_assert(math::Clamp(10.0f, 2.0f, 2.0f) == 2.0f);

    EXPECT_FLOAT_EQ(math::Clamp(-5.0f, 2.0f, 2.0f), 2.0f);
    EXPECT_FLOAT_EQ(math::Clamp( 2.0f, 2.0f, 2.0f), 2.0f);
    EXPECT_FLOAT_EQ(math::Clamp(10.0f, 2.0f, 2.0f), 2.0f);
}

TEST(MathUtilities, ClampNanPassThrough) {
    // With this ternary implementation, if v is NaN then both comparisons evaluate
    // to false, so the function returns v unchanged (NaN is preserved).
    const float nan = std::numeric_limits<float>::quiet_NaN();
    EXPECT_TRUE(std::isnan(math::Clamp(nan, -1.0f, 1.0f)));
}

#pragma endregion

#pragma region UUID

TEST(MathUtilities, UUIDFormat) {
    static const std::regex e("^[0-9a-f]{8}-[0-9a-f]{4}-[0-5][0-9a-f]{3}-[089ab][0-9a-f]{3}-[0-9a-f]{12}$", std::regex_constants::icase);
    EXPECT_TRUE(std::regex_match(math::GenerateUUID(), e));
}

TEST(MathUtilities, UUIDUniqueness) {
    std::set<std::string> uuids;
    for (auto i = 0; i < 1000; i++) {
        const auto uuid = math::GenerateUUID();
        EXPECT_TRUE(uuids.emplace(uuid).second);
    }
}

#pragma endregion