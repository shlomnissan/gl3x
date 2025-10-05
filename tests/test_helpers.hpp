/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include <gtest/gtest.h>

#include <gl3x/math/color.hpp>
#include <gl3x/math/matrix3.hpp>
#include <gl3x/math/matrix4.hpp>
#include <gl3x/math/vector2.hpp>
#include <gl3x/math/vector3.hpp>
#include <gl3x/math/vector4.hpp>

template <typename T>
constexpr bool ApproxEqual(T a, T b, T eps = static_cast<T>(1e-4)) {
    return (a - b < eps) && (b - a < eps);
}

auto EXPECT_MAT3_EQ(const gl3x::Matrix3& a, const gl3x::Matrix3& b) -> void {
    EXPECT_FLOAT_EQ(a(0, 0), b(0, 0));
    EXPECT_FLOAT_EQ(a(0, 1), b(0, 1));
    EXPECT_FLOAT_EQ(a(0, 2), b(0, 2));

    EXPECT_FLOAT_EQ(a(1, 0), b(1, 0));
    EXPECT_FLOAT_EQ(a(1, 1), b(1, 1));
    EXPECT_FLOAT_EQ(a(1, 2), b(1, 2));

    EXPECT_FLOAT_EQ(a(2, 0), b(2, 0));
    EXPECT_FLOAT_EQ(a(2, 1), b(2, 1));
    EXPECT_FLOAT_EQ(a(2, 2), b(2, 2));
}

auto EXPECT_MAT3_NEAR(const gl3x::Matrix3& a, const gl3x::Matrix3& b, float v) -> void {
    EXPECT_NEAR(a(0, 0), b(0, 0), v);
    EXPECT_NEAR(a(0, 1), b(0, 1), v);
    EXPECT_NEAR(a(0, 2), b(0, 2), v);

    EXPECT_NEAR(a(1, 0), b(1, 0), v);
    EXPECT_NEAR(a(1, 1), b(1, 1), v);
    EXPECT_NEAR(a(1, 2), b(1, 2), v);

    EXPECT_NEAR(a(2, 0), b(2, 0), v);
    EXPECT_NEAR(a(2, 1), b(2, 1), v);
    EXPECT_NEAR(a(2, 2), b(2, 2), v);
}

auto EXPECT_MAT4_EQ(const gl3x::Matrix4& a, const gl3x::Matrix4& b) -> void {
    EXPECT_FLOAT_EQ(a(0, 0), b(0, 0));
    EXPECT_FLOAT_EQ(a(0, 1), b(0, 1));
    EXPECT_FLOAT_EQ(a(0, 2), b(0, 2));
    EXPECT_FLOAT_EQ(a(0, 3), b(0, 3));

    EXPECT_FLOAT_EQ(a(1, 0), b(1, 0));
    EXPECT_FLOAT_EQ(a(1, 1), b(1, 1));
    EXPECT_FLOAT_EQ(a(1, 2), b(1, 2));
    EXPECT_FLOAT_EQ(a(1, 3), b(1, 3));

    EXPECT_FLOAT_EQ(a(2, 0), b(2, 0));
    EXPECT_FLOAT_EQ(a(2, 1), b(2, 1));
    EXPECT_FLOAT_EQ(a(2, 2), b(2, 2));
    EXPECT_FLOAT_EQ(a(2, 3), b(2, 3));

    EXPECT_FLOAT_EQ(a(3, 0), b(3, 0));
    EXPECT_FLOAT_EQ(a(3, 1), b(3, 1));
    EXPECT_FLOAT_EQ(a(3, 2), b(3, 2));
    EXPECT_FLOAT_EQ(a(3, 3), b(3, 3));
}

auto EXPECT_MAT4_NEAR(const gl3x::Matrix4& a, const gl3x::Matrix4& b, float v) -> void {
    EXPECT_NEAR(a(0, 0), b(0, 0), v);
    EXPECT_NEAR(a(0, 1), b(0, 1), v);
    EXPECT_NEAR(a(0, 2), b(0, 2), v);
    EXPECT_NEAR(a(0, 3), b(0, 3), v);

    EXPECT_NEAR(a(1, 0), b(1, 0), v);
    EXPECT_NEAR(a(1, 1), b(1, 1), v);
    EXPECT_NEAR(a(1, 2), b(1, 2), v);
    EXPECT_NEAR(a(1, 3), b(1, 3), v);

    EXPECT_NEAR(a(2, 0), b(2, 0), v);
    EXPECT_NEAR(a(2, 1), b(2, 1), v);
    EXPECT_NEAR(a(2, 2), b(2, 2), v);
    EXPECT_NEAR(a(2, 3), b(2, 3), v);

    EXPECT_NEAR(a(3, 0), b(3, 0), v);
    EXPECT_NEAR(a(3, 1), b(3, 1), v);
    EXPECT_NEAR(a(3, 2), b(3, 2), v);
    EXPECT_NEAR(a(3, 3), b(3, 3), v);
}

auto EXPECT_COLOR_EQ(const gl3x::Color& a, const gl3x::Color& b) -> void {
    EXPECT_FLOAT_EQ(a.r, b.r);
    EXPECT_FLOAT_EQ(a.g, b.g);
    EXPECT_FLOAT_EQ(a.b, b.b);
}

auto EXPECT_COLOR_NEAR(const gl3x::Color& a, const gl3x::Color& b, float v) -> void {
    EXPECT_NEAR(a.r, b.r, v);
    EXPECT_NEAR(a.g, b.g, v);
    EXPECT_NEAR(a.b, b.b, v);
}

auto EXPECT_VEC2_EQ(const gl3x::Vector2& a, const gl3x::Vector2& b) -> void {
    EXPECT_EQ(a.x, b.x);
    EXPECT_EQ(a.y, b.y);
}

auto EXPECT_VEC2_NEAR(const gl3x::Vector2& a, const gl3x::Vector2& b, float v) -> void {
    EXPECT_NEAR(a.x, b.x, v);
    EXPECT_NEAR(a.y, b.y, v);
}

auto EXPECT_VEC3_EQ(const gl3x::Vector3& a, const gl3x::Vector3& b) -> void {
    EXPECT_EQ(a.x, b.x);
    EXPECT_EQ(a.y, b.y);
    EXPECT_EQ(a.z, b.z);
}

auto EXPECT_VEC3_NEAR(const gl3x::Vector3& a, const gl3x::Vector3& b, float v) -> void {
    EXPECT_NEAR(a.x, b.x, v);
    EXPECT_NEAR(a.y, b.y, v);
    EXPECT_NEAR(a.z, b.z, v);
}

auto EXPECT_VEC4_EQ(const gl3x::Vector4& a, const gl3x::Vector4& b) -> void {
    EXPECT_EQ(a.x, b.x);
    EXPECT_EQ(a.y, b.y);
    EXPECT_EQ(a.z, b.z);
    EXPECT_EQ(a.w, b.w);
}

auto EXPECT_VEC4_NEAR(const gl3x::Vector4& a, const gl3x::Vector4& b, float v) -> void {
    EXPECT_NEAR(a.x, b.x, v);
    EXPECT_NEAR(a.y, b.y, v);
    EXPECT_NEAR(a.z, b.z, v);
    EXPECT_NEAR(a.w, b.w, v);
}