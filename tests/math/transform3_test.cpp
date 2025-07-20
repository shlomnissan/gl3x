/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gleam/math/transform3.hpp>
#include <gleam/math/utilities.hpp>

#pragma region Mutators

TEST(Transform3, SetPosition) {
    auto t1 = gleam::Transform3 {};
    t1.SetPosition({2.0f, 1.0f, 3.0f});

    EXPECT_VEC3_EQ(t1.position, {2.0f, 1.0f, 3.0f});
    EXPECT_MAT4_EQ(t1.Get(), {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto t2 = []() {
        auto t = gleam::Transform3 {};
        t.SetPosition({2.0f, 1.0f, 3.0f});
        return t;
    }();

    static_assert(t2.position.x == 2.0f);
    static_assert(t2.position.y == 1.0f);
    static_assert(t2.position.z == 3.0f);
}

TEST(Transform3, SetScale) {
    auto t1 = gleam::Transform3 {};
    t1.SetScale({2.0f, 1.0f, 3.0f});

    EXPECT_VEC3_EQ(t1.scale, {2.0f, 1.0f, 3.0f});
    EXPECT_MAT4_EQ(t1.Get(), {
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto t2 = []() {
        auto t = gleam::Transform3 {};
        t.SetScale({2.0f, 1.0f, 3.0f});
        return t;
    }();

    static_assert(t2.scale.x == 2.0f);
    static_assert(t2.scale.y == 1.0f);
    static_assert(t2.scale.z == 3.0f);
}

TEST(Transform3, SetRotation) {
    auto t1 = gleam::Transform3 {};
    auto p = gleam::math::pi_over_2;
    t1.SetRotation(gleam::Euler {p + 0.1f, p + 0.2f, p + 0.3f});

    const auto rotation = t1.rotation;
    EXPECT_NEAR(rotation.pitch, p + 0.1f, 0.0001f);
    EXPECT_NEAR(rotation.yaw, p + 0.2f, 0.0001f);
    EXPECT_NEAR(rotation.roll, p + 0.3f, 0.0001f);

    const auto cos_p = gleam::math::Cos(rotation.pitch);
    const auto sin_p = gleam::math::Sin(rotation.pitch);
    const auto cos_y = gleam::math::Cos(rotation.yaw);
    const auto sin_y = gleam::math::Sin(rotation.yaw);
    const auto cos_r = gleam::math::Cos(rotation.roll);
    const auto sin_r = gleam::math::Sin(rotation.roll);

    EXPECT_MAT4_EQ(t1.Get(), {
        cos_r * cos_y - sin_r * sin_p * sin_y, -sin_r * cos_p, cos_r * sin_y + sin_r * sin_p * cos_y, 0.0f,
        sin_r * cos_y + cos_r * sin_p * sin_y, cos_r * cos_p, sin_r * sin_y - cos_r * sin_p * cos_y, 0.0f,
        -cos_p * sin_y, sin_p, cos_p * cos_y, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto t2 = []() {
        auto t = gleam::Transform3 {};
        auto p = gleam::math::pi_over_2;
        t.SetRotation(gleam::Euler {p + 0.1f, p + 0.2f, p + 0.3f});
        return t;
    }();
}

TEST(Transform3, MultipleTransformations) {
    auto t = gleam::Transform3 {};
    t.SetPosition({2.0f, 1.0f, 3.0f});
    t.SetScale({2.0f, 1.0f, 3.0f});
    t.SetRotation(gleam::Euler {
        gleam::math::pi_over_2 + 0.1f,
        gleam::math::pi_over_2 + 0.2f,
        gleam::math::pi_over_2 + 0.3f
    });

    const auto& rotation = t.rotation;
    const auto& position = t.position;
    const auto& scale = t.scale;
    const auto cos_p = gleam::math::Cos(rotation.pitch);
    const auto sin_p = gleam::math::Sin(rotation.pitch);
    const auto cos_y = gleam::math::Cos(rotation.yaw);
    const auto sin_y = gleam::math::Sin(rotation.yaw);
    const auto cos_r = gleam::math::Cos(rotation.roll);
    const auto sin_r = gleam::math::Sin(rotation.roll);

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
    auto t1 = gleam::Transform3 {};
    t1.Translate({2.0f, 1.0f, 3.0f});
    t1.Translate({1.0f, 1.0f, 0.0f});

    EXPECT_VEC3_EQ(t1.position, {3.0f, 2.0f, 3.0f});
    EXPECT_MAT4_EQ(t1.Get(), {
        1.0f, 0.0f, 0.0f, 3.0f,
        0.0f, 1.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto t2 = []() {
        auto t = gleam::Transform3 {};
        t.Translate({2.0f, 1.0f, 3.0f});
        t.Translate({1.0f, 1.0f, 0.0f});
        return t;
    }();

    static_assert(t2.position.x == 3.0f);
    static_assert(t2.position.y == 2.0f);
    static_assert(t2.position.z == 3.0f);
}

TEST(Transform3, Scale) {
    auto t1 = gleam::Transform3 {};
    t1.Scale({2.0f, 2.0f, 2.0f});
    t1.Scale({3.0f, 3.0f, 2.0f});

    EXPECT_VEC3_EQ(t1.scale, {6.0f, 6.0f, 4.0f});
    EXPECT_MAT4_EQ(t1.Get(), {
        6.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 6.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 4.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto t2 = []() {
        auto t = gleam::Transform3 {};
            t.Scale({2.0f, 2.0f, 2.0f});
            t.Scale({3.0f, 3.0f, 2.0f});
        return t;
    }();

    static_assert(t2.scale.x == 6.0f);
    static_assert(t2.scale.y == 6.0f);
    static_assert(t2.scale.z == 4.0f);
}

TEST(Transform3, RotateX) {
    auto t = gleam::Transform3 {};
    t.Rotate(gleam::Vector3::Right(), gleam::math::pi_over_2);
    t.Rotate(gleam::Vector3::Right(), 0.1f);

    constexpr auto c = gleam::math::Cos(gleam::math::pi_over_2 + 0.1f);
    constexpr auto s = gleam::math::Sin(gleam::math::pi_over_2 + 0.1f);

    EXPECT_MAT4_EQ(t.Get(), {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, c, -s, 0.0f,
        0.0f, s, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto m = []() {
        auto t = gleam::Transform3 {};
        t.Rotate(gleam::Vector3::Right(), gleam::math::pi_over_2);
        t.Rotate(gleam::Vector3::Right(), 0.1f);
        return t.Get();
    }();

    static_assert(m[1].y == c);
    static_assert(m[1].z == s);
    static_assert(m[2].y == -s);
    static_assert(m[2].z == c);
}

TEST(Transform3, RotateY) {
    auto t = gleam::Transform3 {};
    t.Rotate(gleam::Vector3::Up(), gleam::math::pi_over_2);
    t.Rotate(gleam::Vector3::Up(), 0.1f);

    constexpr auto c = gleam::math::Cos(gleam::math::pi_over_2 + 0.1f);
    constexpr auto s = gleam::math::Sin(gleam::math::pi_over_2 + 0.1f);

    EXPECT_MAT4_EQ(t.Get(), {
        c, 0.0f, s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -s, 0.0f, c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto m = []() {
        auto t = gleam::Transform3 {};
        t.Rotate(gleam::Vector3::Up(), gleam::math::pi_over_2);
        t.Rotate(gleam::Vector3::Up(), 0.1f);
        return t.Get();
    }();

    static_assert(m[0].x == c);
    static_assert(m[0].z == -s);
    static_assert(m[2].x == s);
    static_assert(m[2].z == c);
}

TEST(Transform3, RotateZ) {
    auto t = gleam::Transform3 {};
    t.Rotate(gleam::Vector3::Forward(), gleam::math::pi_over_2);
    t.Rotate(gleam::Vector3::Forward(), 0.1f);

    constexpr auto c = gleam::math::Cos(gleam::math::pi_over_2 + 0.1f);
    constexpr auto s = gleam::math::Sin(gleam::math::pi_over_2 + 0.1f);

    EXPECT_MAT4_EQ(t.Get(), {
        c, -s, 0.0f, 0.0f,
        s, c, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto m = []() {
        auto t = gleam::Transform3 {};
        t.Rotate(gleam::Vector3::Forward(), gleam::math::pi_over_2);
        t.Rotate(gleam::Vector3::Forward(), 0.1f);
        return t.Get();
    }();

    static_assert(m[0].x == c);
    static_assert(m[0].y == s);
    static_assert(m[1].x == -s);
    static_assert(m[1].y == c);
}

#pragma endregion

#pragma region Local-Space Translation

TEST(Transform3, TranslateBeforeRotation) {
    auto t = gleam::Transform3 {};
    t.Translate({0.0f, 0.0f, 1.0f});
    t.Rotate(gleam::Vector3::Up(), gleam::math::pi_over_2);

    EXPECT_MAT4_EQ(t.Get(), {
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto m = []() {
        auto t = gleam::Transform3 {};
        t.Translate({0.0f, 0.0f, 1.0f});
        t.Rotate(gleam::Vector3::Up(), gleam::math::pi_over_2);
        return t.Get();
    }();

    static_assert(m[0].x == 0.0f);
    static_assert(m[0].y == 0.0f);
    static_assert(m[0].z == -1.0f);
    static_assert(m[1].x == 0.0f);
    static_assert(m[1].y == 1.0f);
    static_assert(m[1].z == 0.0f);
    static_assert(m[2].x == 1.0f);
    static_assert(m[2].y == 0.0f);
    static_assert(m[2].z == 0.0f);
    static_assert(m[3].x == 0.0f);
    static_assert(m[3].y == 0.0f);
    static_assert(m[3].z == 1.0f);
}

TEST(Transform3, TranslateAfterRotation) {
    auto t = gleam::Transform3 {};
    t.Rotate(gleam::Vector3::Up(), gleam::math::pi_over_2);
    t.Translate({0.0f, 0.0f, 1.0f});

    EXPECT_MAT4_EQ(t.Get(), {
         0.0f, 0.0f, 1.0f, 1.0f,
         0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    });

    constexpr auto m = []() {
        auto t = gleam::Transform3 {};
        t.Rotate(gleam::Vector3::Up(), gleam::math::pi_over_2);
        t.Translate({0.0f, 0.0f, 1.0f});
        return t.Get();
    }();

    static_assert(m[0].x == 0.0f);
    static_assert(m[0].y == 0.0f);
    static_assert(m[0].z == -1.0f);
    static_assert(m[1].x == 0.0f);
    static_assert(m[1].y == 1.0f);
    static_assert(m[1].z == 0.0f);
    static_assert(m[2].x == 1.0f);
    static_assert(m[2].y == 0.0f);
    static_assert(m[2].z == 0.0f);
    static_assert(m[3].x == 1.0f);
    static_assert(m[3].y == 0.0f);
    static_assert(m[3].z == 0.0f);
}

#pragma endregion