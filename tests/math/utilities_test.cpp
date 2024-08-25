// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include "engine/math/utilities.hpp"

#pragma region Degrees and Radians

TEST(MathTests, DegToRad) {
    using namespace engine;

    EXPECT_FLOAT_EQ(math::DegToRad(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::DegToRad(90.0f), math::pi / 2.0f);
    EXPECT_FLOAT_EQ(math::DegToRad(180.0f), math::pi);
    EXPECT_FLOAT_EQ(math::DegToRad(360.0f), math::two_pi);
    EXPECT_FLOAT_EQ(math::DegToRad(45.0f), math::pi / 4.0f);
}

TEST(MathTests, RadToDeg) {
    using namespace engine;

    EXPECT_FLOAT_EQ(math::RadToDeg(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::pi / 2.0f), 90.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::pi), 180.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::two_pi), 360.0f);
    EXPECT_FLOAT_EQ(math::RadToDeg(math::pi / 4.0f), 45.0f);
}

#pragma endregion