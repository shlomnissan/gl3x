/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/vector3.hpp"
#include "gleam/math/matrix4.hpp"

#include <array>

namespace gleam {

class GLEAM_EXPORT Matrix3 {
public:
    Matrix3() = default;

    explicit Matrix3(float value)  : Matrix3(
        value, 0.0f, 0.0f,
        0.0f, value, 0.0f,
        0.0f, 0.0f, value
    ) {}

    Matrix3(
        float n00, float n01, float n02,
        float n10, float n11, float n12,
        float n20, float n21, float n22
    ) : n {
        n00, n10, n20, n01, n11, n21, n02, n12, n22
    } {}

    Matrix3(
        const Vector3& a,
        const Vector3& b,
        const Vector3& c
    ) : n {
        a.x, a.y, a.z,
        b.x, b.y, b.z,
        c.x, c.y, c.z
    } {}

    Matrix3(const Matrix4& m) : Matrix3({
        Vector3(m[0].x, m[0].y, m[0].z),
        Vector3(m[1].x, m[1].y, m[1].z),
        Vector3(m[2].x, m[2].y, m[2].z)
    }) {}

    [[nodiscard]] static auto Identity() {
        return Matrix3 {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
    }

    [[nodiscard]] auto& operator()(int i, int j) {
        return n[j][i];
    }

    [[nodiscard]] const auto& operator()(int i, int j) const {
        return n[j][i];
    }

    [[nodiscard]] auto& operator[](int j) {
        return (*reinterpret_cast<Vector3*>(n[j].data()));
    }

    [[nodiscard]] const auto& operator[](int j) const {
        return (*reinterpret_cast<const Vector3*>(n[j].data()));
    }

private:
    std::array<std::array<float, 3>, 3> n;

    [[nodiscard]] friend auto operator==(const Matrix3& a, const Matrix3& b) -> bool = default;

    [[nodiscard]] friend auto operator*(const Matrix3& a, const Matrix3& b) {
        return Matrix3 {
            a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
            a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
            a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),
            a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
            a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
            a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),
            a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
            a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
            a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2),
        };
    }

    [[nodiscard]] friend auto operator*(const Matrix3& m, const Vector3& v) {
        return Vector3 {
            m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
            m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
            m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z
        };
    }
};

[[nodiscard]] GLEAM_EXPORT inline auto Determinant(const Matrix3& m) {
    return m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1))
         + m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2))
         + m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
}

[[nodiscard]] GLEAM_EXPORT inline auto Inverse(const Matrix3& m) {
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

[[nodiscard]] GLEAM_EXPORT inline auto Transpose(const Matrix3& m) {
    auto output = Matrix3 {};
    output[0] = {m[0][0], m[1][0], m[2][0]};
    output[1] = {m[0][1], m[1][1], m[2][1]};
    output[2] = {m[0][2], m[1][2], m[2][2]};
    return output;
}

}