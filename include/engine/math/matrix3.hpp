// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "vector3.hpp"

namespace engine {

/**
 * @brief A 3x3 matrix class for mathematical operations.
 */
class ENGINE_EXPORT Matrix3 {
public:
    /**
     * @brief Default constructor. Initializes the matrix to a zero matrix.
     */
    Matrix3();

    /**
     * @brief Constructs a new Matrix3 object with the given value.
     *
     * Initializes the matrix as a diagonal matrix where the main diagonal
     * elements are set to the specified value, and all off-diagonal elements
     * are set to zero.
     *
     * @param value The value to set for the diagonal elements of the matrix.
     */
    explicit Matrix3(float value);

    /**
     * @brief Constructs a new Matrix3 object with the given elements.
     *
     * Initializes the matrix with the provided 9 floating-point values in
     * column-major order.
     *
     * @param n00 The element at row 0, column 0.
     * @param n01 The element at row 0, column 1.
     * @param n02 The element at row 0, column 2.
     * @param n10 The element at row 1, column 0.
     * @param n11 The element at row 1, column 1.
     * @param n12 The element at row 1, column 2.
     * @param n20 The element at row 2, column 0.
     * @param n21 The element at row 2, column 1.
     * @param n22 The element at row 2, column 2.
     */
    Matrix3(
        float n00, float n01, float n02,
        float n10, float n11, float n12,
        float n20, float n21, float n22
    );

    /**
     * @brief Constructs a new Matrix3 object using three Vector3 objects as columns.
     *
     * @param a The first column of the matrix.
     * @param b The second column of the matrix.
     * @param c The third column of the matrix.
     */
    Matrix3(
        const Vector3& a,
        const Vector3& b,
        const Vector3& c
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
     * @return Vector3& Reference to the column vector.
     */
    auto& operator[](int j) {
        return (*reinterpret_cast<Vector3*>(n[j]));
    }

    /**
     * @brief Access the column vector at index j
     * (const version).
     *
     * @param j Column index.
     * @return const Vector3& Const reference to the column vector.
     */
    const auto& operator[](int j) const {
        return (*reinterpret_cast<const Vector3*>(n[j]));
    }

private:
    /// @brief Internal storage for the matrix elements in row-major order.
    float n[3][3];
};

/**
 * @brief Multiplies two 3x3 matrices and returns the result.
 * @related Matrix3
 *
 * Performs matrix multiplication between the two input matrices.
 *
 * @param a The first matrix in the multiplication.
 * @param b The second matrix in the multiplication.
 * @return Matrix3 The resulting matrix after multiplication.
 */
inline ENGINE_EXPORT
auto operator*(const Matrix3& a, const Matrix3& b) {
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

};