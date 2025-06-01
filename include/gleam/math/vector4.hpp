// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include <cassert>

namespace engine {

class Vector3;

/**
 * @brief A 4D vector class for mathematical operations.
 */
class GLEAM_EXPORT Vector4 {
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
    Vector4(float value);

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
     * @brief Constructs a Vector4 object from a Vector3 object.
     *
     * @param v The Vector3 object from which to extract the x, y, and z components.
     * @param w The w component of the vector.
     */
    Vector4(const Vector3&v, float w);

    /**
     * @brief Returns a zero vector.
     *
     * @return Vector4 A `Vector4` instance representing the zero vector.
     */
    [[nodiscard]] static auto Zero() { return Vector4 {0.0f}; }

    /**
     * @brief Calculates the length (magnitude) of the vector.
     *
     * @return float The length of the vector.
     */
    [[nodiscard]] auto Length() const -> float;

    /**
     * @brief Calculates the squared length of the vector.
     *
     * @return float The squared length of the vector.
     */
    [[nodiscard]] auto LengthSquared() const -> float;

    /**
     * @brief Accesses the component at the specified index.
     *
     * @param i The index of the component to access (0, 1, 2, or 3).
     * @return float& A reference to the component at the specified index.
     */
    [[nodiscard]] auto& operator[](int i) {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<float*>(this))[i];
    }

    /**
     * @brief Accesses the component at the specified index (const version).
     *
     * @param i The index of the component to access (0, 1, 2, or 3).
     * @return const float& A const reference to the component at the specified index.
     */
    [[nodiscard]] const auto& operator[](int i) const {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<const float*>(this))[i];
    }

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param n The scalar value to multiply with.
     * @return Vector4& A reference to the updated vector.
     */
    auto operator*=(float n) -> Vector4& {
        x *= n;
        y *= n;
        z *= n;
        w *= n;
        return *this;
    }

    /**
     * @brief Multiplies the vector by another vector.
     *
     * @param v The Vector to multiply with.
     * @return Vector4& A reference to the updated vector.
     */
    auto operator*=(const Vector4& v) -> Vector4& {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    /**
     * @brief Adds a vector to the current vector.
     *
     * @param v The vector to add.
     * @return Vector4& A reference to the updated vector.
     */
    auto operator+=(const Vector4& v) -> Vector4& {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    /**
     * @brief Subtracts a vector from the current vector.
     *
     * @param v The vector to subtract.
     * @return Vector4& A reference to the updated vector.
     */
    auto operator-=(const Vector4& v) -> Vector4& {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    /**
     * @brief Normalizes the vector.
     *
     * @return Vector4& A reference to the normalized vector.
     */
    auto Normalize() -> Vector4& {
        const auto len = Length();
        if (len == 0.0f) {
            return *this;
        }
        return *this *= (1.0f / len);
    }

private:
    /**
     * @brief Checks if two vectors are equal, component-wise.
     *
     * @param a The first vector to compare.
     * @param b The second vector to compare.
     * @return bool `true` if the vectors are equal, `false` otherwise.
     */
    [[nodiscard]] friend auto operator==(const Vector4& a, const Vector4& b) -> bool = default;

    /**
     * @brief Adds two vectors component-wise.
     * @related Vector4
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Vector4 A new vector that is the component-wise sum of the two vectors.
     */
    [[nodiscard]] friend auto operator+(const Vector4& a, const Vector4& b) {
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
    [[nodiscard]] friend auto operator-(const Vector4& a, const Vector4& b) {
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
    [[nodiscard]] friend auto operator*(const Vector4& v, float n) {
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
    [[nodiscard]] friend auto operator*(float n, const Vector4& v) {
        return v * n;
    }

    /**
     * @brief Multiplies two vectors component-wise.
     * @related Vector4
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Vector4 A new vector that is the component-wise product of the two input vectors.
     */
    [[nodiscard]] friend auto operator*(const Vector4& a, const Vector4& b) {
        return Vector4 {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    /**
     * @brief Divides the vector by a scalar value.
     * @related Vector4
     *
     * @param v The vector to be divided.
     * @param n The scalar value to divide by.
     * @return Vector4 A new vector that is the result of dividing the original vector by the scalar.
     */
    [[nodiscard]] friend auto operator/(const Vector4& v, float n) {
        n = 1.0f / n;
        return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
    }
};

/**
 * @brief Computes the dot product of two vectors.
 * @related Vector4
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return float A scalar value that is the result of the dot product of the two input vectors.
 */
[[nodiscard]] inline auto Dot(const Vector4& a, const Vector4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
 * @brief Normalizes the vector.
 * @related Vector4
 *
 * @param v The vector to normalize.
 * @return Vector4 A new vector that is the normalized version of the input vector.
 */
[[nodiscard]] inline auto Normalize(const Vector4& v) {
    const auto len = v.Length();
    if (len == 0.0f) {
        return Vector4::Zero();
    }
    return v * (1.0f / len);
}

/**
 * @brief Performs linear interpolation between two vectors.
 * @related Vector4
 *
 * @param v1 The starting vector.
 * @param v2 The ending vector.
 * @param f The interpolation factor (0.0 to 1.0).
 * @return Vector4 A new vector that is the result of the linear interpolation.
 */
[[nodiscard]] inline auto Lerp(const Vector4& v1, const Vector4& v2, float f) {
    return v1 + (v2 - v1) * f;
}

}