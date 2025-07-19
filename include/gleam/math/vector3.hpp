/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/utilities.hpp"

#include <cassert>

namespace gleam {

class Vector3;
auto constexpr Dot(const Vector3& a, const Vector3& b) -> float;

/**
 * @brief A 3D vector class for mathematical operations.
 *
 * @ingroup MathGroup
 */
class GLEAM_EXPORT Vector3 {
public:
    float x; ///< X component of the vector.
    float y; ///< Y component of the vector.
    float z; ///< Z component of the vector.

    /**
     * @brief Default constructor. Initializes to (0, 0, 0).
     */
    constexpr Vector3() = default;

    /**
     * @brief Constructs a vector with all components set to the same value.
     *
     * @param value Value to assign to x, y and z.
     */
    constexpr Vector3(float value) : Vector3(value, value, value) {}

    /**
     * @brief Constructs a vector with specified x, y, and z components.
     *
     * @param x X component.
     * @param y Y component.
     * @param z Z component.
     */
    constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    /**
     * @brief Returns the unit vector pointing forward (0, 0, 1).
     *
     * @return gleam::Vector3
     */
    [[nodiscard]] static constexpr auto Forward() { return Vector3 {0.0f, 0.0f, 1.0f}; }

    /**
     * @brief Returns the unit vector pointing to the right (1, 0, 0).
     *
     * @return gleam::Vector3
     */
    [[nodiscard]] static constexpr auto Right() { return Vector3 {1.0f, 0.0f, 0.0f}; }

    /**
     * @brief Returns the unit vector pointing upward (0, 1, 0).
     *
     * @return gleam::Vector3
     */
    [[nodiscard]] static constexpr auto Up() { return Vector3 {0.0f, 1.0f, 0.0f}; }

    /**
     * @brief Returns a zero vector (0, 0, 0).
     *
     * @return gleam::Vector3
     */
    [[nodiscard]] static constexpr auto Zero() { return Vector3 {0.0f}; }

    /**
     * @brief Computes the approximate magnitude of the vector.
     *
     * This function uses a fast inverse square root approximation to compute the
     * square root, which is significantly faster than the standard library `sqrt`,
     * but introduces a small precision error (~0.001%).
     *
     * @return float Approximate vector length.
     */
    [[nodiscard]] constexpr auto Length() const { return math::Sqrt(Dot(*this, *this)); }

    /**
     * @brief Computes the squared length (magnitude) of the vector.
     *
     * This is a precise and inexpensive operation that avoids computing a square root.
     * Use this when comparing relative lengths or avoiding unnecessary precision loss.
     *
     * @return float Exact length squared.
     */
    [[nodiscard]] constexpr auto LengthSquared() const { return Dot(*this, *this); }

    /**
     * @brief Accesses vector components by index.
     *
     * @param i Index (0 for x, 1 for y, 2 for z).
     * @return float Reference to component.
     */
    [[nodiscard]] constexpr auto& operator[](int i) {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return x; // placeholder
        }
    }

    /**
     * @brief Accesses vector components by index (const).
     *
     * @param i Index (0 for x, 1 for y, 2 for z).
     * @return float Const reference to component.
     */
    [[nodiscard]] constexpr const auto& operator[](int i) const {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return x; // placeholder
        }
    }

    /// @brief Adds another vector to this one.
    constexpr auto& operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    /// @brief Subtracts another vector from this one.
    constexpr auto& operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    /// @brief Scales the vector by a scalar.
    constexpr auto& operator*=(float n) {
        x *= n;
        y *= n;
        z *= n;
        return *this;
    }

    /// @brief Scales each component by another vector.
    constexpr auto& operator*=(const Vector3& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    /**
     * @brief Normalizes the vector in-place.
     *
     * If the length is zero, the vector is left unchanged.
     *
     * @return gleam::Vector3 Reference to this vector.
     */
    constexpr auto& Normalize() {
        const auto len = Length();
        return len == 0.0f ? *this : (*this *= (1.0f / len));
    }

private:
    /// @brief Equality comparison operator.
    [[nodiscard]] friend constexpr auto operator==(const Vector3& a, const Vector3& b) -> bool = default;

    /// @brief Vector addition.
    [[nodiscard]] friend constexpr auto operator+(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    /// @brief Vector subtraction.
    [[nodiscard]] friend constexpr auto operator-(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    /// @brief Scalar multiplication (vector * scalar).
    [[nodiscard]] friend constexpr auto operator*(const Vector3& v, float n) {
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }

    /// @brief Scalar multiplication (scalar * vector).
    [[nodiscard]] friend constexpr auto operator*(float n, const Vector3& v) {
        return v * n;
    }

    /// @brief Component-wise multiplication.
    [[nodiscard]] friend constexpr auto operator*(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    /// @brief Scalar division.
    [[nodiscard]] friend constexpr auto operator/(const Vector3& v, float n) {
        n = 1.0f / n;
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }
};

/**
 * @brief Computes the cross product between two vectors.
 * @relatesalso Vector3
 *
 * @param a First vector.
 * @param b Second vector.
 * @return gleam::Vector3 Cross product (a × b).
 */
[[nodiscard]] inline constexpr auto Cross(const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

/**
 * @brief Computes the dot product between two vectors.
 * @relatesalso Vector3
 *
 * @param a First vector.
 * @param b Second vector.
 * @return float Dot product (a · b).
 */
[[nodiscard]] inline constexpr auto Dot(const Vector3& a, const Vector3& b) -> float {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief Linearly interpolates between two vectors.
 * @relatesalso Vector3
 *
 * @param v1 Start vector.
 * @param v2 End vector.
 * @param f Interpolation factor [0, 1].
 * @return gleam::Vector3 Interpolated vector.
 */
[[nodiscard]] inline constexpr auto Lerp(const Vector3& v1, const Vector3& v2, float f) {
    return v1 + (v2 - v1) * f;
}

/**
 * @brief Returns a normalized copy of the given vector.
 * @relatesalso Vector3
 *
 * @param v Input vector.
 * @return gleam::Vector3 Normalized vector or zero if the input is zero-length.
 */
[[nodiscard]] inline constexpr auto Normalize(const Vector3& v) {
    const auto len = v.Length();
    return len == 0.0f ? Vector3::Zero() : v * (1.0f / len);
}

}