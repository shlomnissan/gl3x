// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "vector4.hpp"

namespace engine {

/**
 * @brief A 4x4 matrix class for mathematical operations.
 */
class ENGINE_EXPORT Matrix4 {
public:
    /**
     * @brief Default constructor. Initializes the matrix to a zero matrix.
     */
    Matrix4();

    /**
     * @brief Constructs a new Matrix4 object with the given value.
     *
     * Initializes the matrix as a diagonal matrix where the main diagonal
     * elements are set to the specified value, and all off-diagonal elements
     * are set to zero.
     *
     * @param value The value to set for the diagonal elements of the matrix.
     */
    explicit Matrix4(float value);

    /**
     * @brief Constructs a new Matrix4 object with the given elements.
     *
     * Initializes the matrix with the provided 16 floating-point values in
     * column-major order.
     *
     * @param n00 The element at row 0, column 0.
     * @param n01 The element at row 0, column 1.
     * @param n02 The element at row 0, column 2.
     * @param n03 The element at row 0, column 3.
     * @param n10 The element at row 1, column 0.
     * @param n11 The element at row 1, column 1.
     * @param n12 The element at row 1, column 2.
     * @param n13 The element at row 1, column 3.
     * @param n20 The element at row 2, column 0.
     * @param n21 The element at row 2, column 1.
     * @param n22 The element at row 2, column 2.
     * @param n23 The element at row 2, column 3.
     * @param n30 The element at row 3, column 0.
     * @param n31 The element at row 3, column 1.
     * @param n32 The element at row 3, column 2.
     * @param n33 The element at row 3, column 3.
     */
    Matrix4(
        float n00, float n01, float n02, float n03,
        float n10, float n11, float n12, float n13,
        float n20, float n21, float n22, float n23,
        float n30, float n31, float n32, float n33
    );

    /**
     * @brief Constructs a new Matrix4 object using four Vector4 objects as columns.
     *
     * @param a The first column of the matrix.
     * @param b The second column of the matrix.
     * @param c The third column of the matrix.
     * @param d The fourth column of the matrix.
     */
    Matrix4(
        const Vector4& a,
        const Vector4& b,
        const Vector4& c,
        const Vector4& d
    );

    /**
     * @brief Access matrix element at (i, j) with row-major indexing.
     *
     * @param i Row index.
     * @param j Column index.
     * @return float& Reference to the matrix element.
     */
    auto& operator()(int i, int j) {
        return n[j][i];
    }

    /**
     * @brief Access matrix element at (i, j) with row-major indexing
     * (const version).
     *
     * @param i Row index.
     * @param j Column index.
     * @return const float& Const reference to the matrix element.
     */
    const auto& operator()(int i, int j) const {
        return n[j][i];
    }

    /**
     * @brief Access the column vector at index j.
     *
     * @param j Column index.
     * @return Vector4& Reference to the column vector.
     */
    auto& operator[](int j) {
        return (*reinterpret_cast<Vector4*>(n[j]));
    }

    /**
     * @brief Access the column vector at index j
     * (const version).
     *
     * @param j Column index.
     * @return const Vector4& Const reference to the column vector.
     */
    const auto& operator[](int j) const {
        return (*reinterpret_cast<const Vector4*>(n[j]));
    }

private:
    /// @brief Internal storage for the matrix elements in row-major order.
    float n[4][4];

    /**
    * @brief Checks if two matrices are equal, component-wise.
    *
    * @param a The first matrix to compare.
    * @param b The second matrix to compare.
    * @return bool `true` if the matrices are equal, `false` otherwise.
    */
    friend bool operator==(const Matrix4& a, const Matrix4& b) = default;
};

/**
 * @brief Multiplies two 4x4 matrices and returns the result.
 * @related Matrix4
 *
 * Performs matrix multiplication between the two input matrices.
 *
 * @param a The first matrix in the multiplication.
 * @param b The second matrix in the multiplication.
 * @return Matrix4 The resulting matrix after multiplication.
 */
inline ENGINE_EXPORT
auto operator*(const Matrix4& a, const Matrix4& b) {
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

}