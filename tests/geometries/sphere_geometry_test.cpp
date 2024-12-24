// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/geometries/sphere_geometry.hpp>

#pragma region Assertions

TEST(SphereGeometry, DeathWhenParamsAreInvalid) {
    EXPECT_DEATH({
        engine::SphereGeometry({.radius = 0.0f});
    }, ".*params.radius > 0.0f");

    EXPECT_DEATH({
        engine::SphereGeometry({.width_segments = 2});
    }, ".params.width_segments >= 3");

    EXPECT_DEATH({
        engine::SphereGeometry({.height_segments = 1});
    }, ".params.height_segments >= 2");

    EXPECT_DEATH({
        engine::SphereGeometry({.phi_start = -0.1f});
    }, ".*params.phi_start >= 0.0f");

    EXPECT_DEATH({
        engine::SphereGeometry({.phi_length = -0.1f});
    }, ".*params.phi_length >= 0.0f");

    EXPECT_DEATH({
        engine::SphereGeometry({.theta_start = -0.1f});
    }, ".*params.theta_start >= 0.0f");

    EXPECT_DEATH({
        engine::SphereGeometry({.theta_length = -0.1f});
    }, ".*params.theta_length >= 0.0f");
}

#pragma endregion