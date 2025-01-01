// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "engine/math/matrix4.hpp"

namespace engine {

Matrix4::Matrix4() : Matrix4(0.0f) {}

Matrix4::Matrix4(float value) : Matrix4(
    value, 0.0f, 0.0f, 0.0f,
    0.0f, value, 0.0f, 0.0f,
    0.0f, 0.0f, value, 0.0f,
    0.0f, 0.0f, 0.0f, value
) {}

Matrix4::Matrix4(
    float n00, float n01, float n02, float n03,
    float n10, float n11, float n12, float n13,
    float n20, float n21, float n22, float n23,
    float n30, float n31, float n32, float n33
) : n {
    n00, n10, n20, n30,
    n01, n11, n21, n31,
    n02, n12, n22, n32,
    n03, n13, n23, n33
} {}

Matrix4::Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d) : n {
    a.x, a.y, a.z, a.w,
    b.x, b.y, b.z, b.w,
    c.x, c.y, c.z, c.w,
    d.x, d.y, d.z, d.w
} {}

auto Determinant(const Matrix4& m) -> float {
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

auto Inverse(const Matrix4& m) -> Matrix4 {
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

auto Transpose(const Matrix4& m) -> Matrix4 {
    auto output = Matrix4 {};
    output[0] = {m[0][0], m[1][0], m[2][0], m[3][0]};
    output[1] = {m[0][1], m[1][1], m[2][1], m[3][1]};
    output[2] = {m[0][2], m[1][2], m[2][2], m[3][2]};
    output[3] = {m[0][3], m[1][3], m[2][3], m[3][3]};
    return output;
}

}