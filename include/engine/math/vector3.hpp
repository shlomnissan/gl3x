// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <cassert>

namespace engine {

/**
 * @brief A 3D vector class for mathematical operations.
 */
class ENGINE_EXPORT Vector3 {
public:
    /// @brief The x component of the vector.
    float x;
    /// @brief The y component of the vector.
    float y;
    /// @brief The z component of the vector.
    float z;

    /**
     * @brief Default constructor that initializes the vector to (0, 0, 0).
     */
    Vector3();

    /**
     * @brief Constructs a vector with all components initialized to the given value.
     *
     * @param value The value to initialize all components of the vector.
     */
    explicit Vector3(float value);

    /**
     * @brief Constructs a vector with the specified x, y, and z components.
     *
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     * @param z The z component of the vector.
     */
    Vector3(float x, float y, float z);

    /**
     * @brief Returns a unit vector along the X axis.
     *
     * @return Vector3 A `Vector3` instance representing the X unit vector.
     */
    [[nodiscard]]
    static auto Right() { return Vector3 {1.0f, 0.0f, 0.0f}; }

    /**
     * @brief Returns a unit vector along the Y axis.
     *
     * @return Vector3 A `Vector3` instance representing the Y unit vector.
     */
    [[nodiscard]]
    static auto Up() { return Vector3 {0.0f, 1.0f, 0.0f}; }

    /**
     * @brief Returns a unit vector along the Z axis.
     *
     * @return Vector3 A `Vector3` instance representing the Z unit vector.
     */
    [[nodiscard]]
    static auto Forward() { return Vector3 {0.0f, 0.0f, 1.0f}; }

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
     * @param i The index of the component to access (0, 1, or 2).
     * @return float& A reference to the component at the specified index.
     */
    [[nodiscard]]
    auto& operator[](int i) {
        assert(i >= 0 && i < 3);
        return (reinterpret_cast<float*>(this))[i];
    }

    /**
     * @brief Accesses the component at the specified index (const version).
     *
     * @param i The index of the component to access (0, 1, or 2).
     * @return const float& A const reference to the component at the specified index.
     */
    [[nodiscard]]
    const auto& operator[](int i) const {
        assert(i >= 0 && i < 3);
        return (reinterpret_cast<const float*>(this))[i];
    }

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param n The scalar value to multiply with.
     * @return Vector3& A reference to the updated vector.
     */
    auto operator*=(float n) -> Vector3& {
        x *= n;
        y *= n;
        z *= n;
        return *this;
    }

private:
    /**
     * @brief Checks if two vectors are equal, component-wise.
     *
     * @param a The first vector to compare.
     * @param b The second vector to compare.
     * @return bool `true` if the vectors are equal, `false` otherwise.
     */
    [[nodiscard]]
    friend bool operator==(const Vector3& a, const Vector3& b) = default;

    /**
     * @brief Adds two vectors component-wise.
     * @related Vector3
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Vector3 A new vector that is the component-wise sum of the two vectors.
     */
    [[nodiscard]]
    friend auto operator+(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    /**
     * @brief Subtracts the second vector from the first vector component-wise.
     * @related Vector3
     *
     * @param a The vector to subtract from.
     * @param b The vector to subtract.
     * @return Vector3 A new vector that is the component-wise difference of the two vectors.
     */
    [[nodiscard]]
    friend auto operator-(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    /**
     * @brief Multiplies the vector by a scalar value.
     * @related Vector3
     *
     * @param v The vector to be scaled.
     * @param n The scalar value to multiply with.
     * @return Vector3 A new vector that is the result of scaling the original vector.
     */
    [[nodiscard]]
    friend auto operator*(const Vector3& v, float n) {
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }

    /**
     * @brief Multiplies a scalar value by a vector.
     * @related Vector3
     *
     * @param n The scalar value to multiply with.
     * @param v The vector to be scaled.
     * @return Vector3 A new vector that is the result of scaling the original vector.
     */
    [[nodiscard]]
    friend auto operator*(float n, const Vector3& v) {
        return v * n;
    }

    /**
     * @brief Multiplies two vectors component-wise.
     * @related Vector3
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Vector3 A new vector that is the component-wise product of the two input vectors.
     */
    [[nodiscard]]
    friend auto operator*(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    /**
     * @brief Divides the vector by a scalar value.
     * @related Vector3
     *
     * @param v The vector to be divided.
     * @param n The scalar value to divide by.
     * @return Vector3 A new vector that is the result of dividing the original vector by the scalar.
     */
    [[nodiscard]]
    friend auto operator/(const Vector3& v, float n) {
        n = 1.0f / n;
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }
};

/**
 * @brief Computes the cross product of two vectors.
 * @related Vector3
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return Vector3 A new vector that is the result of the cross product of the two input vectors.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto Cross(const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

/**
 * @brief Computes the dot product of two vectors.
 * @related Vector3
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return float A scalar value that is the result of the dot product of the two input vectors.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto Dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief Normalizes the vector.
 * @related Vector3
 *
 * @param v The vector to normalize.
 * @return Vector3 A new vector that is the normalized version of the input vector.
 *         If the input vector has zero length, returns a zero vector.
 */
[[nodiscard]] inline ENGINE_EXPORT
auto Normalize(const Vector3& v) {
    const auto len = v.length();
    if (len == 0.0f) {
        return Vector3 {0.0f};
    }
    return v * (1.0f / len);
}

}