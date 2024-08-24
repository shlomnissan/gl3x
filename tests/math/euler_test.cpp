// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include <engine/math/euler.hpp>

#pragma region Equality Operator

TEST(Euler, EqualityOperator) {
    using enum engine::Euler::RotationOrder;

    const auto e1 = engine::Euler {0.5f, 0.2f, 0.0f, XYZ};
    const auto e2 = engine::Euler {0.5f, 0.2f, 0.0f, XYZ};
    const auto e3 = engine::Euler {0.1f, 0.2f, 0.0f, YXZ};

    EXPECT_TRUE(e1 == e2);
    EXPECT_FALSE(e1 == e3);
}

TEST(Euler, InequalityOperator) {
    using enum engine::Euler::RotationOrder;

    const auto e1 = engine::Euler {0.5f, 0.2f, 0.0f, XYZ};
    const auto e2 = engine::Euler {0.5f, 0.2f, 0.0f, XYZ};
    const auto e3 = engine::Euler {0.1f, 0.2f, 0.0f, YXZ};

    EXPECT_FALSE(e1 != e2);
    EXPECT_TRUE(e1 != e3);
}

#pragma endregion