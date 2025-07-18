/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include <gtest/gtest.h>
#include <test_helpers.hpp>

#include <gleam/math/transform2.hpp>
#include <gleam/math/utilities.hpp>

#pragma region Mutators

TEST(Transform2, SetPosition) {
    auto t = gleam::Transform2 {};
    t.SetPosition({2.0f, 1.0f});

    EXPECT_VEC2_EQ(t.GetPosition(), {2.0f, 1.0f});
    EXPECT_MAT3_EQ(t.Get(), {
        1.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, SetScale) {
    auto t = gleam::Transform2 {};
    t.SetScale({2.0f, 1.0f});

    EXPECT_VEC2_EQ(t.GetScale(), {2.0f, 1.0f});
    EXPECT_MAT3_EQ(t.Get(), {
        2.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, SetRotation) {
    auto t = gleam::Transform2 {};
    t.SetRotation(gleam::math::pi_over_2);

    auto r = t.GetRotation();
    auto c = gleam::math::Cos(r);
    auto s = gleam::math::Sin(r);
    EXPECT_EQ(t.GetRotation(), r);
    EXPECT_MAT3_EQ(t.Get(), {
        c, -s, 0.0f,
        s, c, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, MultipleTransformations) {
    auto t = gleam::Transform2 {};
    t.SetCenter({0.5f, 0.5f});
    t.SetPosition({2.0f, 3.0f});
    t.SetScale({2.0f, 2.0f});
    t.SetRotation(gleam::math::pi_over_2);

    auto c = gleam::math::Cos(t.GetRotation()) * t.GetScale().x;
    auto s = gleam::math::Sin(t.GetRotation()) * t.GetScale().y;
    EXPECT_VEC2_EQ(t.GetCenter(), {0.5f, 0.5f});
    EXPECT_VEC2_EQ(t.GetPosition(), {2.0f, 3.0f});
    EXPECT_VEC2_EQ(t.GetScale(), {2.0f, 2.0f});
    EXPECT_EQ(t.GetRotation(), gleam::math::pi_over_2);
    EXPECT_MAT3_EQ(t.Get(), {
        c, -s, 3.5f,
        s, c, 2.5f,
        0.0f, 0.0f, 1.0f
    });
}

#pragma endregion

#pragma region Cumulative Transformations

TEST(Transform2, Translate) {
    auto t = gleam::Transform2 {};
    t.Translate({2.0f, 1.0f});

    EXPECT_VEC2_EQ(t.GetPosition(), {2.0f, 1.0f});
    EXPECT_MAT3_EQ(t.Get(), {
        1.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, Scale) {
    auto t = gleam::Transform2 {};
    t.Scale({2.0f, 1.0f});

    EXPECT_VEC2_EQ(t.GetScale(), {2.0f, 1.0f});
    EXPECT_MAT3_EQ(t.Get(), {
        2.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, Rotate) {
    auto t = gleam::Transform2 {};
    t.Rotate(gleam::math::pi_over_2);

    auto c = gleam::math::Cos(t.GetRotation());
    auto s = gleam::math::Sin(t.GetRotation());
    EXPECT_EQ(t.GetRotation(), gleam::math::pi_over_2);
    EXPECT_MAT3_EQ(t.Get(), {
        c, -s, 0.0f,
        s, c, 0.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, TransformationsWithOffset) {
    auto t = gleam::Transform2 {};
    t.SetCenter({0.5, 0.5f});
    t.Translate({2.0f, 3.0f});
    t.Scale({2.0f, 2.0f});
    t.Rotate(gleam::math::pi_over_2);

    auto c = gleam::math::Cos(t.GetRotation()) * t.GetScale().x;
    auto s = gleam::math::Sin(t.GetRotation()) * t.GetScale().y;
    EXPECT_VEC2_EQ(t.GetCenter(), {0.5f, 0.5f});
    EXPECT_VEC2_EQ(t.GetPosition(), {2.0f, 3.0f});
    EXPECT_VEC2_EQ(t.GetScale(), {2.0f, 2.0f});
    EXPECT_EQ(t.GetRotation(), gleam::math::pi_over_2);
    EXPECT_MAT3_EQ(t.Get(), {
        c, -s, 3.5f,
        s, c, 2.5f,
        0.0f, 0.0f, 1.0f
    });
}

#pragma endregion

#pragma region Local-Space Translation

TEST(Transform2, TranslateBeforeRotation) {
    auto t = gleam::Transform2 {};
    t.Translate({0.0f, 1.0f});
    t.Rotate(gleam::math::pi_over_2);

    auto c = gleam::math::Cos(t.GetRotation());
    auto s = gleam::math::Sin(t.GetRotation());
    EXPECT_VEC2_EQ(t.GetPosition(), {0.0f, 1.0f});
    EXPECT_MAT3_EQ(t.Get(), {
        c, -s, 0.0f,
        s,  c, 1.0f,
        0.0f, 0.0f, 1.0f
    });
}

TEST(Transform2, TranslateAfterRotation) {
    auto t = gleam::Transform2 {};
    t.Rotate(gleam::math::pi_over_2);
    t.Translate({0.0f, 1.0f});

    auto c = gleam::math::Cos(t.GetRotation());
    auto s = gleam::math::Sin(t.GetRotation());
    EXPECT_VEC2_NEAR(t.GetPosition(), {-1.0f, 0.0f}, 0.001f);
    EXPECT_MAT3_NEAR(t.Get(), {
        c, -s, -1.0f,
        s,  c,  0.0f,
        0.0f, 0.0f, 1.0f
    }, 0.0001f);
}

#pragma endregion