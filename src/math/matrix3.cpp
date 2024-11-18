// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/matrix3.hpp"

namespace engine {

Matrix3::Matrix3() : Matrix3(0.0f) {}

Matrix3::Matrix3(float value) : Matrix3(
    value, 0.0f, 0.0f,
    0.0f, value, 0.0f,
    0.0f, 0.0f, value
) {}

Matrix3::Matrix3(
    float n00, float n01, float n02,
    float n10, float n11, float n12,
    float n20, float n21, float n22
) : n {
    n00, n10, n20, n01, n11, n21, n02, n12, n22
} {}

Matrix3::Matrix3(const Vector3& a, const Vector3& b, const Vector3& c) : n {
    a.x, a.y, a.z,
    b.x, b.y, b.z,
    c.x, c.y, c.z
} {}

Matrix3::Matrix3(const Matrix4& m) : Matrix3({m[0], m[1], m[2]}) {}

auto Determinant(const Matrix3& m) -> float {
    return m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1))
         + m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2))
         + m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
}

auto Inverse(const Matrix3& m) -> Matrix3 {
    const auto& a = m[0];
    const auto& b = m[1];
    const auto& c = m[2];

    auto r0 = Cross(b, c);
    auto r1 = Cross(c, a);
    auto r2 = Cross(a, b);

    auto inv_det = 1.0f / Dot(r2, c);

    return Matrix3 {
        r0.x * inv_det, r0.y * inv_det, r0.z * inv_det,
        r1.x * inv_det, r1.y * inv_det, r1.z * inv_det,
        r2.x * inv_det, r2.y * inv_det, r2.z * inv_det
    };
}

auto Transpose(const Matrix3& m) -> Matrix3 {
    auto output = Matrix3 {};
    output[0] = {m[0][0], m[1][0], m[2][0]};
    output[1] = {m[0][1], m[1][1], m[2][1]};
    output[2] = {m[0][2], m[1][2], m[2][2]};
    return output;
}

}