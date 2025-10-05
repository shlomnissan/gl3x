/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/vector3.hpp"
#include "gl3x/math/matrix4.hpp"

#include <array>

namespace gl3x {

/**
 * @brief A 3x3 matrix class for mathematical operations.
 *
 * Stores the matrix in column-major order using three Vector3 columns.
 * Commonly used for representing linear transformations.
 *
 * @ingroup MathGroup
 */
class GL3X_EXPORT Matrix3 {
public:
    /**
     * @brief Constructs a Matrix3 object. Leaves the contents uninitialized.
     */
    constexpr Matrix3() = default;

    /**
     * @brief Constructs a diagonal Matrix3 with the given scalar value.
     *
     * @param value Value to place on the diagonal.
     */
    explicit constexpr Matrix3(float value) : Matrix3({
        value, 0.0f, 0.0f,
        0.0f, value, 0.0f,
        0.0f, 0.0f, value
    }) {}

    /**
     * @brief Constructs a Matrix3 object from individual components (row-major).
     *
     * @param n00 First row, first element.
     * @param n01 First row, second element.
     * @param n02 First row, third element.
     * @param n10 Second row, first element.
     * @param n11 Second row, second element.
     * @param n12 Second row, third element.
     * @param n20 Third row, first element.
     * @param n21 Third row, second element.
     * @param n22 Third row, third element.
     */
    constexpr Matrix3(
        float n00, float n01, float n02,
        float n10, float n11, float n12,
        float n20, float n21, float n22
    ) : m {{
        Vector3(n00, n10, n20),
        Vector3(n01, n11, n21),
        Vector3(n02, n12, n22)
    }} {}

    /**
     * @brief Constructs a Matrix3 object from three column vectors.
     *
     * @param a First column vector.
     * @param b Second column vector.
     * @param c Third column vector.
     */
    constexpr Matrix3(
        const Vector3& a,
        const Vector3& b,
        const Vector3& c
    ) : m {{a, b, c}} {}

    /**
     * @brief Constructs a Matrix3 object from a Matrix4.
     *
     * Extracts the upper-left 3x3 submatrix from a 4x4 matrix.
     *
     * @param m 4x4 matrix.
     */
    constexpr Matrix3(const Matrix4& m) : Matrix3(
        m[0].x, m[1].x, m[2].x,
        m[0].y, m[1].y, m[2].y,
        m[0].z, m[1].z, m[2].z
    ) {}

    /**
     * @brief Returns the identity matrix.
     */
    [[nodiscard]] static constexpr auto Identity() {
        return Matrix3 {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
    }

    /**
     * @brief Access matrix element by (row, column).
     *
     * @param i Row index (0 to 2).
     * @param j Column index (0 to 2).
     * @return Reference to the element.
     */
    [[nodiscard]] constexpr auto& operator()(int i, int j) {
        return m[j][i];
    }

    /**
     * @brief Access matrix element by (row, column) (const).
     *
     * @param i Row index (0 to 2).
     * @param j Column index (0 to 2).
     * @return Const reference to the element.
     */
    [[nodiscard]] constexpr const auto& operator()(int i, int j) const {
        return m[j][i];
    }

    /**
     * @brief Access matrix column vector by index.
     *
     * @param j Column index (0 to 2).
     * @return Reference to the column.
     */
    [[nodiscard]] constexpr auto& operator[](int j) {
        return m[j];
    }

    /**
     * @brief Access matrix column vector by index (const).
     *
     * @param j Column index (0 to 2).
     * @return Const reference to the column.
     */
    [[nodiscard]] constexpr const auto& operator[](int j) const {
        return m[j];
    }

private:
    std::array<Vector3, 3> m; ///< Matrix stored in column-major order.

    /// @brief Equality comparison operator.
    [[nodiscard]] friend constexpr auto operator==(const Matrix3& a, const Matrix3& b) -> bool = default;

    /// @brief Matrix-matrix multiplication.
    [[nodiscard]] friend constexpr auto operator*(const Matrix3& a, const Matrix3& b) {
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

    /// @brief Matrix-vector multiplication.
    [[nodiscard]] friend constexpr auto operator*(const Matrix3& m, const Vector3& v) {
        return Vector3 {
            m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
            m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
            m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z
        };
    }
};

/**
 * @brief Computes the determinant of a Matrix3 object.
 * @relatesalso Matrix3
 *
 * @param m Input matrix.
 * @return Determinant value.
 */
[[nodiscard]] GL3X_EXPORT inline constexpr auto Determinant(const Matrix3& m) {
    return m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1))
         + m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2))
         + m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
}

/**
 * @brief Computes the inverse of a Matrix3 object.
 * @relatesalso Matrix3
 *
 * @param m Input matrix.
 * @return Inverse matrix.
 */
[[nodiscard]] GL3X_EXPORT inline constexpr auto Inverse(const Matrix3& m) {
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

/**
 * @brief Computes the transpose of a Matrix3 object.
 * @relatesalso Matrix3
 *
 * @param m Input matrix.
 * @return Transposed matrix.
 */
[[nodiscard]] GL3X_EXPORT inline constexpr auto Transpose(const Matrix3& m) {
    auto output = Matrix3 {};
    output[0] = {m[0][0], m[1][0], m[2][0]};
    output[1] = {m[0][1], m[1][1], m[2][1]};
    output[2] = {m[0][2], m[1][2], m[2][2]};
    return output;
}

}