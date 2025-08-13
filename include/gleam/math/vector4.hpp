/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/utilities.hpp"

#include <algorithm>
#include <cassert>

namespace gleam {

class Vector4;
auto constexpr Dot(const Vector4& a, const Vector4& b) -> float;

/**
 * @brief A 4D vector class for mathematical operations.
 *
 * @ingroup MathGroup
 */
class GLEAM_EXPORT Vector4 {
public:
    float x; ///< X component of the vector.
    float y; ///< Y component of the vector.
    float z; ///< Z component of the vector.
    float w; ///< W component of the vector.

    /**
     * @brief Default constructor. Initializes to (0, 0, 0, 0).
     */
    constexpr Vector4() = default;

    /**
     * @brief Constructs a vector with all components set to the same value.
     *
     * @param value Value to assign to x, y, z, and w.
     */
    constexpr Vector4(float value) : Vector4(value, value, value, value) {}

    /**
     * @brief Constructs a vector with specified x, y, z, and w components.
     *
     * @param x X component.
     * @param y Y component.
     * @param z Z component.
     * @param w W component.
     */
    constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    /**
     * @brief Returns a zero vector (0, 0, 0, 0).
     *
     * @return gleam::Vector4
     */
    [[nodiscard]] static constexpr auto Zero() { return Vector4 {0.0f}; }

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
     * @param i Index (0 for x, 1 for y, 2 for z, 3 for w).
     * @return float Reference to component.
     */
    [[nodiscard]] constexpr auto& operator[](int i) {
        assert(i >= 0 && i < 4);
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: return x; // placeholder
        }
    }

    /**
     * @brief Accesses vector components by index (const).
     *
     * @param i Index (0 for x, 1 for y, 2 for z, 3 for w).
     * @return float Const reference to component.
     */
    [[nodiscard]] constexpr const auto& operator[](int i) const {
        assert(i >= 0 && i < 4);
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: return x; // placeholder
        }
    }

    /// @brief Adds another vector to this one.
    constexpr auto& operator+=(const Vector4& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    /// @brief Subtracts another vector from this one.
    constexpr auto& operator-=(const Vector4& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    /// @brief Scales the vector by a scalar.
    constexpr auto& operator*=(float n) {
        x *= n;
        y *= n;
        z *= n;
        w *= n;
        return *this;
    }

    /// @brief Scales each component by another vector.
    constexpr auto& operator*=(const Vector4& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    /**
     * @brief Component-wise in-place minimum.
     *
     * Sets each component of this vector to the smaller of the corresponding components
     * in this vector and the given vector @p v.
     *
     * @param v Vector to compare against.
     * @return gleam::Vector4 Reference to this vector after modification.
     */
    constexpr auto& Min(const Vector4& v) noexcept {
        x = std::min(x, v.x);
        y = std::min(y, v.y);
        z = std::min(z, v.z);
        w = std::min(w, v.w);
        return *this;
    };

    /**
     * @brief Component-wise in-place maximum.
     *
     * Sets each component of this vector to the larger of the corresponding components
     * in this vector and the given vector @p v.
     *
     * @param v Vector to compare against.
     * @return gleam::Vector4 Reference to this vector after modification.
     */
    constexpr auto& Max(const Vector4& v) noexcept {
        x = std::max(x, v.x);
        y = std::max(y, v.y);
        z = std::max(z, v.z);
        w = std::max(w, v.w);
        return *this;
    };

    /**
     * @brief Normalizes the vector in-place.
     *
     * If the length is zero, the vector is left unchanged.
     *
     * @return gleam::Vector4 Reference to this vector.
     */
    constexpr auto& Normalize() {
        const auto len = Length();
        return len == 0.0f ? *this : (*this *= (1.0f / len));
    }

private:
    /// @brief Equality comparison operator.
    [[nodiscard]] friend constexpr auto operator==(const Vector4& a, const Vector4& b) -> bool = default;

    /// @brief Vector addition.
    [[nodiscard]] friend constexpr auto operator+(const Vector4& a, const Vector4& b) {
        return Vector4 {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    }

    /// @brief Vector subtraction.
    [[nodiscard]] friend constexpr auto operator-(const Vector4& a, const Vector4& b) {
        return Vector4 {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    }

    /// @brief Scalar multiplication (vector * scalar).
    [[nodiscard]] friend constexpr auto operator*(const Vector4& v, float n) {
        return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
    }

    /// @brief Scalar multiplication (scalar * vector).
    [[nodiscard]] friend constexpr auto operator*(float n, const Vector4& v) {
        return v * n;
    }

    /// @brief Component-wise multiplication.
    [[nodiscard]] friend constexpr auto operator*(const Vector4& a, const Vector4& b) {
        return Vector4 {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    /// @brief Scalar division.
    [[nodiscard]] friend constexpr auto operator/(const Vector4& v, float n) {
        n = 1.0f / n;
        return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
    }
};

/**
 * @brief Computes the dot product between two vectors.
 * @relatesalso Vector4
 *
 * @param a First vector.
 * @param b Second vector.
 * @return float Dot product (a · b).
 */
[[nodiscard]] inline constexpr auto Dot(const Vector4& a, const Vector4& b) -> float {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
 * @brief Linearly interpolates between two vectors.
 * @relatesalso Vector4
 *
 * @param v1 Start vector.
 * @param v2 End vector.
 * @param f Interpolation factor [0, 1].
 * @return gleam::Vector4 Interpolated vector.
 */
[[nodiscard]] inline constexpr auto Lerp(const Vector4& v1, const Vector4& v2, float f) {
    return v1 + (v2 - v1) * f;
}

/**
 * @brief Returns a normalized copy of the given vector.
 * @relatesalso Vector4
 *
 * @param v Input vector.
 * @return gleam::Vector4 Normalized vector or zero if the input is zero-length.
 */
[[nodiscard]] inline constexpr auto Normalize(const Vector4& v) {
    const auto len = v.Length();
    return len == 0.0f ? Vector4::Zero() : v * (1.0f / len);
}

}