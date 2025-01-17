// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/euler.hpp>
#include <engine/math/matrix4.hpp>
#include <engine/math/vector3.hpp>
#include <engine/math/utilities.hpp>

#include <cmath>

auto Rotate(float angle, const engine::Vector3& v) -> engine::Matrix4;

#pragma region Constructor

TEST(Euler, ConstructorWithEulerAngles) {
    const auto e = engine::Euler {{.pitch = 0.5f, .yaw = 0.2f, .roll = 0.3f}};

    EXPECT_FLOAT_EQ(e.pitch, 0.5f);
    EXPECT_FLOAT_EQ(e.yaw, 0.2f);
    EXPECT_FLOAT_EQ(e.roll, 0.3f);
}

TEST(Euler, ConstructorWithMatrix) {
    const auto in = engine::Euler {{.pitch = 0.5f, .yaw = 0.2f, .roll = 0.3f}};
    const auto out = engine::Euler {in.GetMatrix()};

    EXPECT_NEAR(in.pitch, out.pitch, 1e-6);
    EXPECT_NEAR(in.yaw, out.yaw, 1e-6);
    EXPECT_NEAR(in.roll, out.roll, 1e-6);
}

#pragma endregion

#pragma region Get Matrix

TEST(Euler, GetMatrixBasic) {
    const auto e = engine::Euler {{.pitch = 0.5f, .yaw = 0.2f, .roll = 0.3f}};
    const auto m = e.GetMatrix();

    const auto rotation_x = Rotate(e.pitch, engine::Vector3::Right());
    const auto rotation_y = Rotate(e.yaw, engine::Vector3::Up());
    const auto rotation_z = Rotate(e.roll, engine::Vector3::Forward());

    const auto expected = rotation_z * rotation_x * rotation_y;
    EXPECT_MAT4_EQ(m, expected);
}

#pragma endregion

#pragma region Edge Cases

TEST(Euler, ConstrucotrWithMatrixGimbalLock) {
    const auto pitch = engine::math::half_pi;
    const auto yaw = 0.0f;
    const auto roll = 0.0f;

    const auto e = engine::Euler {{.pitch = pitch, .yaw = yaw, .roll = roll}};
    const auto m = e.GetMatrix();
    const auto output = engine::Euler {m};

    // Check if the pitch is correctly identified as 90 degrees
    EXPECT_NEAR(output.pitch, pitch, 1e-6);

    // In gimbal lock, yaw and roll are not uniquely determined
    // We can only check if the sum of yaw and roll is correct
    EXPECT_NEAR(output.yaw + output.roll, yaw + roll, 1e-6);
}


#pragma endregion

#pragma region Equality Operator

TEST(Euler, EqualityOperator) {
    const auto e1 = engine::Euler {{.pitch = 0.5f, .yaw = 0.2f, .roll = 0.0f}};
    const auto e2 = engine::Euler {{.pitch = 0.5f, .yaw = 0.2f, .roll = 0.0f}};
    const auto e3 = engine::Euler {{.pitch = 0.1f, .yaw = 0.2f, .roll = 0.0f}};

    EXPECT_TRUE(e1 == e2);
    EXPECT_FALSE(e1 == e3);
}

TEST(Euler, InequalityOperator) {
    const auto e1 = engine::Euler {{.pitch = 0.5f, .yaw = 0.2f, .roll = 0.0f}};
    const auto e2 = engine::Euler {{.pitch = 0.5f, .yaw = 0.2f, .roll = 0.0f}};
    const auto e3 = engine::Euler {{.pitch = 0.1f, .yaw = 0.2f, .roll = 0.0f}};

    EXPECT_FALSE(e1 != e2);
    EXPECT_TRUE(e1 != e3);
}

#pragma endregion

#pragma region Helpers

auto Rotate(float angle, const engine::Vector3& v) -> engine::Matrix4 {
    const auto a = angle;
    const auto c = std::cos(a);
    const auto s = std::sin(a);
    const auto axis = Normalize(v);
    const auto temp = (1.0f - c) * axis;

    return {
        c + temp[0] * axis[0], temp[1] * axis[0] - s * axis[2], temp[2] * axis[0] + s * axis[1], 0.0f,
        temp[0] * axis[1] + s * axis[2], c + temp[1] * axis[1], temp[2] * axis[1] - s * axis[0], 0.0f,
        temp[0] * axis[2] - s * axis[1], temp[1] * axis[2] + s * axis[0], c + temp[2] * axis[2], 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

#pragma endregion