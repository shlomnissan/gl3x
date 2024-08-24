// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <cassert>

namespace engine {

/**
 * @brief A 4D vector class for mathematical operations.
 */
class ENGINE_EXPORT Vector4 {
public:
    /// @brief The x component of the vector.
    float x;
    /// @brief The y component of the vector.
    float y;
    /// @brief The z component of the vector.
    float z;
    /// @brief The w component of the vector.
    float w;

    /**
     * @brief Default constructor that initializes the vector to (0, 0, 0, 0).
     */
    Vector4();

    /**
     * @brief Constructs a vector with all components initialized to the given value.
     *
     * @param value The value to initialize all components of the vector.
     */
    explicit Vector4(float value);

    /**
     * @brief Constructs a vector with the specified x, y, z, and w components.
     *
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     * @param z The z component of the vector.
     * @param w The w component of the vector.
     */
    Vector4(float x, float y, float z, float w);

    /**
     * @brief Calculates the length (magnitude) of the vector.
     *
     * @return float The length of the vector.
     */
    [[nodiscard]]
    auto length() const -> float;

    /**
     * @brief Accesses the component at the specified index.
     *
     * @param i The index of the component to access (0, 1, 2, or 3).
     * @return float& A reference to the component at the specified index.
     */
    [[nodiscard]]
    auto& operator[](int i) {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<float*>(this))[i];
    }

    /**
     * @brief Accesses the component at the specified index (const version).
     *
     * @param i The index of the component to access (0, 1, 2, or 3).
     * @return const float& A const reference to the component at the specified index.
     */
    [[nodiscard]]
    const auto& operator[](int i) const {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<const float*>(this))[i];
    }

    /**
    * @brief Checks if two vectors are equal, component-wise.
    *
    * @param a The first vector to compare.
    * @param b The second vector to compare.
    * @return bool `true` if the vectors are equal, `false` otherwise.
    */
    friend bool operator==(const Vector4& a, const Vector4& b) = default;
};

/**
 * @brief Adds two vectors component-wise.
 * @related Vector4
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return Vector4 A new vector that is the component-wise sum of the two vectors.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto operator+(const Vector4& a, const Vector4& b) {
    return Vector4 {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

/**
 * @brief Subtracts the second vector from the first vector component-wise.
 * @related Vector4
 *
 * @param a The vector to subtract from.
 * @param b The vector to subtract.
 * @return Vector4 A new vector that is the component-wise difference of the two vectors.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto operator-(const Vector4& a, const Vector4& b) {
    return Vector4 {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

/**
 * @brief Multiplies the vector by a scalar value.
 * @related Vector4
 *
 * @param v The vector to be scaled.
 * @param n The scalar value to multiply with.
 * @return Vector4 A new vector that is the result of scaling the original vector.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto operator*(const Vector4& v, float n) {
    return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
}

/**
 * @brief Multiplies a scalar value by a vector.
 * @related Vector4
 *
 * @param n The scalar value to multiply with.
 * @param v The vector to be scaled.
 * @return Vector4 A new vector that is the result of scaling the original vector.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto operator*(float n, const Vector4& v) {
    return v * n;
}

/**
 * @brief Divides the vector by a scalar value.
 * @related Vector4
 *
 * @param v The vector to be divided.
 * @param n The scalar value to divide by.
 * @return Vector4 A new vector that is the result of dividing the original vector by the scalar.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto operator/(const Vector4& v, float n) {
    n = 1.0 / n;
    return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
}

/**
 * @brief Computes the dot product of two vectors.
 * @related Vector4
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return float A scalar value that is the result of the dot product of the two input vectors.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto dot(const Vector4& a, const Vector4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
 * @brief Normalizes the vector.
 * @related Vector4
 *
 * @param v The vector to normalize.
 * @return Vector4 A new vector that is the normalized version of the input vector.
 *         If the input vector has zero length, returns a zero vector.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto normalize(const Vector4& v) {
    const auto len = v.length();
    if (len == 0.0f) {
        return Vector4 {0.0f};
    }
    return v * (1.0f / len);
}

}