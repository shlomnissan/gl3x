/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/vector3.hpp"
#include "gleam/math/vector4.hpp"

#include <array>

namespace gleam {

class GLEAM_EXPORT Matrix4 {
public:
    Matrix4() = default;

    explicit Matrix4(float value) : Matrix4(
        value, 0.0f, 0.0f, 0.0f,
        0.0f, value, 0.0f, 0.0f,
        0.0f, 0.0f, value, 0.0f,
        0.0f, 0.0f, 0.0f, value
    ) {}

    constexpr Matrix4(
        float n00, float n01, float n02, float n03,
        float n10, float n11, float n12, float n13,
        float n20, float n21, float n22, float n23,
        float n30, float n31, float n32, float n33
    ) : m {{
        Vector4(n00, n10, n20, n30),
        Vector4(n01, n11, n21, n31),
        Vector4(n02, n12, n22, n32),
        Vector4(n03, n13, n23, n33)
    }} {}

    Matrix4(
        const Vector4& a,
        const Vector4& b,
        const Vector4& c,
        const Vector4& d
    ) : m {{a, b, c, d}} {}

    [[nodiscard]] static auto Identity() {
        return Matrix4 {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    [[nodiscard]] auto& operator()(int i, int j) {
        return m[j][i];
    }

    [[nodiscard]] const auto& operator()(int i, int j) const {
        return m[j][i];
    }

    [[nodiscard]] constexpr auto& operator[](int j) {
        return m[j];
    }

    [[nodiscard]] constexpr const auto& operator[](int j) const {
        return m[j];
    }

private:
    std::array<Vector4, 4> m;

    [[nodiscard]] friend auto operator==(const Matrix4& a, const Matrix4& b) -> bool = default;

    [[nodiscard]] friend auto operator*(const Matrix4& a, const Matrix4& b) {
        return Matrix4 {
            a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
            a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1),
            a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) + a(0, 3) * b(3, 2),
            a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) * b(3, 3),
            a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) + a(1, 3) * b(3, 0),
            a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + a(1, 3) * b(3, 1),
            a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) + a(1, 3) * b(3, 2),
            a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) * b(3, 3),
            a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) + a(2, 3) * b(3, 0),
            a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) + a(2, 3) * b(3, 1),
            a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 2),
            a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3) * b(3, 3),
            a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + a(3, 3) * b(3, 0),
            a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + a(3, 3) * b(3, 1),
            a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + a(3, 3) * b(3, 2),
            a(3, 0) * b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) + a(3, 3) * b(3, 3)
        };
    }

    [[nodiscard]] friend auto operator*(const Matrix4& m, const Vector4& v) {
        return Vector4 {
            m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w,
            m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w,
            m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w,
            m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z + m(3, 3) * v.w
        };
    }

    [[nodiscard]] friend auto operator*(const Matrix4& m, const Vector3& v) {
        return Vector3 {
            m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * 1.0f,
            m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * 1.0f,
            m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * 1.0f
        };
    }
};

[[nodiscard]] GLEAM_EXPORT inline auto Determinant(const Matrix4& m) {
    return m(0, 0) * (
        m(1, 1) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) -
        m(1, 2) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
        m(1, 3) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1))
    ) - m(0, 1) * (
        m(1, 0) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) -
        m(1, 2) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) +
        m(1, 3) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0))
    ) + m(0, 2) * (
        m(1, 0) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) -
        m(1, 1) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) +
        m(1, 3) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0))
    ) - m(0, 3) * (
        m(1, 0) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)) -
        m(1, 1) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
        m(1, 2) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0))
    );
}

[[nodiscard]] GLEAM_EXPORT inline auto Inverse(const Matrix4& m) {
    const auto& a = reinterpret_cast<const Vector3&>(m[0]);
    const auto& b = reinterpret_cast<const Vector3&>(m[1]);
    const auto& c = reinterpret_cast<const Vector3&>(m[2]);
    const auto& d = reinterpret_cast<const Vector3&>(m[3]);

    const float& x = m(3, 0);
    const float& y = m(3, 1);
    const float& z = m(3, 2);
    const float& w = m(3, 3);

    auto s = Cross(a, b);
    auto t = Cross(c, d);
    auto u = (a * y) - (b * x);
    auto v = (c * w) - (d * z);

    const auto inv_det = 1.0f / (Dot(s, v) + Dot(t, u));
    s *= inv_det;
    t *= inv_det;
    u *= inv_det;
    v *= inv_det;

    auto r0 = Cross(b, v) + t * y;
    auto r1 = Cross(v, a) - t * x;
    auto r2 = Cross(d, u) + s * w;
    auto r3 = Cross(u, c) - s * z;

    return Matrix4 {
        r0.x, r0.y, r0.z, -Dot(b, t),
        r1.x, r1.y, r1.z,  Dot(a, t),
        r2.x, r2.y, r2.z, -Dot(d, s),
        r3.x, r3.y, r3.z,  Dot(c, s)
    };
}

[[nodiscard]] GLEAM_EXPORT inline auto Transpose(const Matrix4& m) {
    auto output = Matrix4 {};
    output[0] = {m[0][0], m[1][0], m[2][0], m[3][0]};
    output[1] = {m[0][1], m[1][1], m[2][1], m[3][1]};
    output[2] = {m[0][2], m[1][2], m[2][2], m[3][2]};
    output[3] = {m[0][3], m[1][3], m[2][3], m[3][3]};
    return output;
}

}