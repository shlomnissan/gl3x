/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/vector3.hpp"
#include "gl3x/math/vector4.hpp"

#include <array>

namespace gleam {

/**
 * @brief A 4x4 matrix class for mathematical operations.
 *
 * Stores the matrix in column-major order using four Vector4 columns.
 * Commonly used for 3D transformations including translation, rotation, scaling, and projection.
 *
 * @ingroup MathGroup
 */
class GL3X_EXPORT Matrix4 {
public:
    /**
     * @brief Constructs a Matrix4 object. Leaves the contents uninitialized.
     */
    constexpr Matrix4() = default;

    /**
     * @brief Constructs a diagonal Matrix4 with the given scalar value.
     *
     * @param value Value to place on the diagonal.
     */
    explicit constexpr Matrix4(float value) : Matrix4(
        value, 0.0f, 0.0f, 0.0f,
        0.0f, value, 0.0f, 0.0f,
        0.0f, 0.0f, value, 0.0f,
        0.0f, 0.0f, 0.0f, value
    ) {}

    /**
     * @brief Constructs a Matrix4 object from individual components (row-major).
     *
     * @param n00 First row, first element.
     * @param n01 First row, second element.
     * @param n02 First row, third element.
     * @param n03 First row, fourth element.
     * @param n10 Second row, first element.
     * @param n11 Second row, second element.
     * @param n12 Second row, third element.
     * @param n13 Second row, fourth element.
     * @param n20 Third row, first element.
     * @param n21 Third row, second element.
     * @param n22 Third row, third element.
     * @param n23 Third row, fourth element.
     * @param n30 Fourth row, first element.
     * @param n31 Fourth row, second element.
     * @param n32 Fourth row, third element.
     * @param n33 Fourth row, fourth element.
     */
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

    /**
     * @brief Constructs a Matrix4 object from four column vectors.
     *
     * @param a First column vector.
     * @param b Second column vector.
     * @param c Third column vector.
     * @param d Fourth column vector.
     */
    constexpr Matrix4(
        const Vector4& a,
        const Vector4& b,
        const Vector4& c,
        const Vector4& d
    ) : m {{a, b, c, d}} {}

    /**
     * @brief Returns the identity matrix.
     */
    [[nodiscard]] static constexpr auto Identity() {
        return Matrix4 {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    /**
     * @brief Access matrix element by (row, column).
     *
     * @param i Row index (0 to 3).
     * @param j Column index (0 to 3).
     * @return Reference to the element.
     */
    [[nodiscard]] constexpr auto& operator()(int i, int j) {
        return m[j][i];
    }

    /**
     * @brief Access matrix element by (row, column) (const).
     *
     * @param i Row index (0 to 3).
     * @param j Column index (0 to 3).
     * @return Const reference to the element.
     */
    [[nodiscard]] constexpr const auto& operator()(int i, int j) const {
        return m[j][i];
    }

    /**
     * @brief Access matrix column vector by index.
     *
     * @param j Column index (0 to 3).
     * @return Reference to the column.
     */
    [[nodiscard]] constexpr auto& operator[](int j) {
        return m[j];
    }

    /**
     * @brief Access matrix column vector by index (const).
     *
     * @param j Column index (0 to 3).
     * @return Const reference to the column.
     */
    [[nodiscard]] constexpr const auto& operator[](int j) const {
        return m[j];
    }

private:
    std::array<Vector4, 4> m; ///< Matrix stored in column-major order.

    /// @brief Equality comparison operator.
    [[nodiscard]] friend constexpr auto operator==(const Matrix4& a, const Matrix4& b) -> bool = default;

    /// @brief Matrix-matrix multiplication.
    [[nodiscard]] friend constexpr auto operator*(const Matrix4& a, const Matrix4& b) {
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

    /// @brief Matrix-vector multiplication with Vector4.
    [[nodiscard]] friend constexpr auto operator*(const Matrix4& m, const Vector4& v) {
        return Vector4 {
            m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w,
            m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w,
            m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w,
            m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z + m(3, 3) * v.w
        };
    }

    /// @brief Matrix-vector multiplication with Vector3 (implicitly using w=1).
    [[nodiscard]] friend constexpr auto operator*(const Matrix4& m, const Vector3& v) {
        return Vector3 {
            m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * 1.0f,
            m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * 1.0f,
            m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * 1.0f
        };
    }
};

/**
 * @brief Computes the determinant of a Matrix4 object.
 * @relatesalso Matrix4
 *
 * @param m Input matrix.
 * @return Determinant value.
 */
[[nodiscard]] GL3X_EXPORT inline constexpr auto Determinant(const Matrix4& m) {
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

/**
 * @brief Computes the inverse of a Matrix4 object.
 * @relatesalso Matrix4
 *
 * @param m Input matrix.
 * @return Inverse matrix.
 */
[[nodiscard]] GL3X_EXPORT inline constexpr auto Inverse(const Matrix4& m) {
    const auto& a = Vector3 {m[0].x, m[0].y, m[0].z};
    const auto& b = Vector3 {m[1].x, m[1].y, m[1].z};
    const auto& c = Vector3 {m[2].x, m[2].y, m[2].z};
    const auto& d = Vector3 {m[3].x, m[3].y, m[3].z};

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

/**
 * @brief Computes the transpose of a Matrix4 object.
 * @relatesalso Matrix4
 *
 * @param m Input matrix.
 * @return Transposed matrix.
 */
[[nodiscard]] GL3X_EXPORT inline constexpr auto Transpose(const Matrix4& m) {
    auto output = Matrix4 {};
    output[0] = {m[0][0], m[1][0], m[2][0], m[3][0]};
    output[1] = {m[0][1], m[1][1], m[2][1], m[3][1]};
    output[2] = {m[0][2], m[1][2], m[2][2], m[3][2]};
    output[3] = {m[0][3], m[1][3], m[2][3], m[3][3]};
    return output;
}

}