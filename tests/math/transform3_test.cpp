// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <engine/math/transform3.hpp>
#include <engine/math/utilities.hpp>

#include <cmath>

#pragma region Transformations

TEST(Transform3, SetPosition) {
    auto t = engine::Transform3 {};
    t.SetPosition({2.0f, 1.0f, 3.0f});

    EXPECT_VEC3_EQ(t.GetPosition(), {2.0f, 1.0f, 3.0f});
    EXPECT_MAT4_EQ(t.Get(), {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3, SetScale) {
    auto t = engine::Transform3 {};
    t.SetScale({2.0f, 1.0f, 3.0f});

    EXPECT_VEC3_EQ(t.GetScale(), {2.0f, 1.0f, 3.0f});
    EXPECT_MAT4_EQ(t.Get(), {
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3, SetRotation) {
    auto t = engine::Transform3 {};
    auto p = engine::math::half_pi;
    t.SetRotation(engine::Euler {{
        .pitch = p + 0.1f,
        .yaw = p + 0.2f,
        .roll = p + 0.3f
    }});

    const auto rotation = t.GetRotation();
    EXPECT_NEAR(rotation.pitch, p + 0.1f, 0.0001f);
    EXPECT_NEAR(rotation.yaw, p + 0.2f, 0.0001f);
    EXPECT_NEAR(rotation.roll, p + 0.3f, 0.0001f);

    const auto cos_p = std::cos(rotation.pitch);
    const auto sin_p = std::sin(rotation.pitch);
    const auto cos_y = std::cos(rotation.yaw);
    const auto sin_y = std::sin(rotation.yaw);
    const auto cos_r = std::cos(rotation.roll);
    const auto sin_r = std::sin(rotation.roll);

    EXPECT_MAT4_EQ(t.Get(), {
        cos_r * cos_y - sin_r * sin_p * sin_y, -sin_r * cos_p, cos_r * sin_y + sin_r * sin_p * cos_y, 0.0f,
        sin_r * cos_y + cos_r * sin_p * sin_y, cos_r * cos_p, sin_r * sin_y - cos_r * sin_p * cos_y, 0.0f,
        -cos_p * sin_y, sin_p, cos_p * cos_y, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3, MultipleTransformations) {
    auto t = engine::Transform3 {};
    t.SetPosition({2.0f, 1.0f, 3.0f});
    t.SetScale({2.0f, 1.0f, 3.0f});
    t.SetRotation(engine::Euler {{
        .pitch = engine::math::half_pi + 0.1f,
        .yaw = engine::math::half_pi + 0.2f,
        .roll = engine::math::half_pi + 0.3f
    }});

    const auto& rotation = t.GetRotation();
    const auto& position = t.GetPosition();
    const auto& scale = t.GetScale();
    const auto cos_p = std::cos(rotation.pitch);
    const auto sin_p = std::sin(rotation.pitch);
    const auto cos_y = std::cos(rotation.yaw);
    const auto sin_y = std::sin(rotation.yaw);
    const auto cos_r = std::cos(rotation.roll);
    const auto sin_r = std::sin(rotation.roll);

    EXPECT_MAT4_EQ(t.Get(), {
        scale.x * (cos_r * cos_y - sin_r * sin_p * sin_y),
        scale.y * (-sin_r * cos_p),
        scale.z * (cos_r * sin_y + sin_r * sin_p * cos_y),
        position.x,

        scale.x * (sin_r * cos_y + cos_r * sin_p * sin_y),
        scale.y * (cos_r * cos_p),
        scale.z * (sin_r * sin_y - cos_r * sin_p * cos_y),
        position.y,

        scale.x * (-cos_p * sin_y),
        scale.y * sin_p,
        scale.z * (cos_p * cos_y),
        position.z,

        0.0f, 0.0f, 0.0f, 1.0f
    });
}

#pragma endregion

#pragma region Cumulative Transformations

TEST(Transform3, Translate) {
    auto t = engine::Transform3 {};
    t.Translate({2.0f, 1.0f, 3.0f});
    t.Translate({1.0f, 1.0f, 0.0f});

    EXPECT_VEC3_EQ(t.GetPosition(), {3.0f, 2.0f, 3.0f});
    EXPECT_MAT4_EQ(t.Get(), {
        1.0f, 0.0f, 0.0f, 3.0f,
        0.0f, 1.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3, Scale) {
    auto t = engine::Transform3 {};
    t.Scale({2.0f, 2.0f, 2.0f});
    t.Scale({3.0f, 3.0f, 2.0f});

    EXPECT_VEC3_EQ(t.GetScale(), {6.0f, 6.0f, 4.0f});
    EXPECT_MAT4_EQ(t.Get(), {
        6.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 6.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 4.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3, RotateX) {
    auto t = engine::Transform3 {};
    t.Rotate(engine::Vector3::Right(), engine::math::half_pi);
    t.Rotate(engine::Vector3::Right(), 0.1f);

    auto c = std::cos(t.GetRotation().pitch);
    auto s = std::sin(t.GetRotation().pitch);
    EXPECT_EQ(t.GetRotation().pitch, engine::math::half_pi + 0.1f);
    EXPECT_MAT4_EQ(t.Get(), {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, c, -s, 0.0f,
        0.0f, s, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3, RotateY) {
    auto t = engine::Transform3 {};
    t.Rotate(engine::Vector3::Up(), engine::math::half_pi);
    t.Rotate(engine::Vector3::Up(), 0.1f);

    auto c = std::cos(t.GetRotation().yaw);
    auto s = std::sin(t.GetRotation().yaw);
    EXPECT_EQ(t.GetRotation().yaw, engine::math::half_pi + 0.1f);
    EXPECT_MAT4_EQ(t.Get(), {
        c, 0.0f, s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -s, 0.0f, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

TEST(Transform3, RotateZ) {
    auto t = engine::Transform3 {};
    t.Rotate(engine::Vector3::Forward(), engine::math::half_pi);
    t.Rotate(engine::Vector3::Forward(), 0.1f);

    auto c = std::cos(t.GetRotation().roll);
    auto s = std::sin(t.GetRotation().roll);
    EXPECT_EQ(t.GetRotation().roll, engine::math::half_pi + 0.1f);
    EXPECT_MAT4_EQ(t.Get(), {
        c, -s, 0.0f, 0.0f,
        s, c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
}

#pragma endregion