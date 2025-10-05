/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/math/utilities.hpp"

#include <algorithm>
#include <cassert>

namespace gl3x {

class Vector2;
auto constexpr Dot(const Vector2& a, const Vector2& b) -> float;

/**
 * @brief A 2D vector class for mathematical operations.
 *
 * @ingroup MathGroup
 */
class GL3X_EXPORT Vector2 {
public:
    float x; ///< X component of the vector.
    float y; ///< Y component of the vector.

    /**
     * @brief Default constructor. Initializes to (0, 0).
     */
    constexpr Vector2() = default;

    /**
     * @brief Constructs a vector with both components set to the same value.
     *
     * @param value Value to assign to both x and y.
     */
    constexpr Vector2(float value) : Vector2(value, value) {}

    /**
     * @brief Constructs a vector with specified x and y components.
     *
     * @param x X component.
     * @param y Y component.
     */
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    /**
     * @brief Returns the unit vector pointing to the right (1, 0).
     *
     * @return gl3x::Vector2
     */
    [[nodiscard]] static constexpr auto Right() { return Vector2 {1.0f, 0.0f}; }

    /**
     * @brief Returns the unit vector pointing upward (0, 1).
     *
     * @return gl3x::Vector2
     */
    [[nodiscard]] static constexpr auto Up() { return Vector2 {0.0f, 1.0f}; }

    /**
     * @brief Returns a zero vector (0, 0).
     *
     * @return gl3x::Vector2
     */
    [[nodiscard]] static constexpr auto Zero() { return Vector2 {0.0f}; }

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
     * @param i Index (0 for x, 1 for y).
     * @return float Reference to component.
     */
    [[nodiscard]] constexpr auto& operator[](int i) {
        assert(i >= 0 && i < 2);
        switch (i) {
            case 0: return x;
            case 1: return y;
            default: return x; // placeholder
        }
    }

    /**
     * @brief Accesses vector components by index (const).
     *
     * @param i Index (0 for x, 1 for y).
     * @return float Const reference to component.
     */
    [[nodiscard]] constexpr const auto& operator[](int i) const {
        assert(i >= 0 && i < 2);
        switch (i) {
            case 0: return x;
            case 1: return y;
            default: return x; // placeholder
        }
    }

    /// @brief Adds another vector to this one.
    constexpr auto& operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    /// @brief Subtracts another vector from this one.
    constexpr auto& operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    /// @brief Scales the vector by a scalar.
    constexpr auto& operator*=(float n) {
        x *= n;
        y *= n;
        return *this;
    }

    /// @brief Scales each component by another vector.
    constexpr auto& operator*=(const Vector2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    /**
     * @brief Component-wise in-place minimum.
     *
     * Sets each component of this vector to the smaller of the corresponding components
     * in this vector and the given vector @p v.
     *
     * @param v Vector to compare against.
     * @return gl3x::Vector2 Reference to this vector after modification.
     */
    constexpr auto& Min(const Vector2& v) noexcept {
        x = std::min(x, v.x);
        y = std::min(y, v.y);
        return *this;
    };

    /**
     * @brief Component-wise in-place maximum.
     *
     * Sets each component of this vector to the larger of the corresponding components
     * in this vector and the given vector @p v.
     *
     * @param v Vector to compare against.
     * @return gl3x::Vector2 Reference to this vector after modification.
     */
    constexpr auto& Max(const Vector2& v) noexcept {
        x = std::max(x, v.x);
        y = std::max(y, v.y);
        return *this;
    };

    /**
     * @brief Normalizes the vector in-place.
     *
     * If the length is zero, the vector is left unchanged.
     *
     * @return gl3x::Vector2 Reference to this vector.
     */
    constexpr auto& Normalize() {
        const auto len = Length();
        return len == 0.0f ? *this : (*this *= (1.0f / len));
    }

private:
    /// @brief Equality comparison operator.
    [[nodiscard]] friend constexpr auto operator==(const Vector2& a, const Vector2& b) -> bool = default;

    /// @brief Vector addition.
    [[nodiscard]] friend constexpr auto operator+(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x + b.x, a.y + b.y};
    }

    /// @brief Vector subtraction.
    [[nodiscard]] friend constexpr auto operator-(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x - b.x, a.y - b.y};
    }

    /// @brief Scalar multiplication (vector * scalar).
    [[nodiscard]] friend constexpr auto operator*(const Vector2& v, float n) {
        return Vector2 {v.x * n, v.y * n};
    }

    /// @brief Scalar multiplication (scalar * vector).
    [[nodiscard]] friend constexpr auto operator*(float n, const Vector2& v) {
        return v * n;
    }

    /// @brief Component-wise multiplication.
    [[nodiscard]] friend constexpr auto operator*(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x * b.x, a.y * b.y};
    }

    /// @brief Scalar division.
    [[nodiscard]] friend constexpr auto operator/(const Vector2& v, float n) {
        n = 1.0f / n;
        return Vector2 {v.x * n, v.y * n};
    }
};

/**
 * @brief Computes the dot product between two vectors.
 * @relatesalso Vector2
 *
 * @param a First vector.
 * @param b Second vector.
 * @return float Dot product (a · b).
 */
[[nodiscard]] inline constexpr auto Dot(const Vector2& a, const Vector2& b) -> float {
    return a.x * b.x + a.y * b.y;
}

/**
 * @brief Linearly interpolates between two vectors.
 * @relatesalso Vector2
 *
 * @param v1 Start vector.
 * @param v2 End vector.
 * @param f Interpolation factor [0, 1].
 * @return gl3x::Vector2 Interpolated vector.
 */
[[nodiscard]] inline constexpr auto Lerp(const Vector2& v1, const Vector2& v2, float f) {
    return v1 + (v2 - v1) * f;
}

/**
 * @brief Returns a normalized copy of the given vector.
 * @relatesalso Vector2
 *
 * @param v Input vector.
 * @return Vector2 Normalized vector or zero if the input is zero-length.
 */
[[nodiscard]] inline constexpr auto Normalize(const Vector2& v) {
    const auto len = v.Length();
    return len == 0.0f ? Vector2::Zero() : v * (1.0f / len);
}

}