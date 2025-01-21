// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

namespace engine {

/**
 * @brief A 2D vector class for mathematical operations.
 */
class ENGINE_EXPORT Vector2 {
public:
    /// @brief The x component of the vector.
    float x;
    /// @brief The y component of the vector.
    float y;

    /**
     * @brief Default constructor that initializes the vector to (0, 0).
     */
    Vector2();

    /**
     * @brief Constructs a vector with all components initialized to the given value.
     *
     * @param value The value to initialize all components of the vector.
     */
    explicit Vector2(float value);

    /**
     * @brief Constructs a vector with the specified x and y components.
     *
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     */
    Vector2(float x, float y);

    /**
     * @brief Adds a vector to the current vector.
     *
     * @param v The vector to add.
     * @return Vector2& A reference to the updated vector.
     */
    auto operator+=(const Vector2& v) -> Vector2& {
        x += v.x;
        y += v.y;
        return *this;
    }

    /**
     * @brief Subtracts a vector from the current vector.
     *
     * @param v The vector to subtract.
     * @return Vector2& A reference to the updated vector.
     */
    auto operator-=(const Vector2& v) -> Vector2& {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    /**
     * @brief Multiplies the vector by a scalar value.
     *
     * @param n The scalar value to multiply with.
     * @return Vector2& A reference to the updated vector.
     */
    auto operator*=(float n) -> Vector2& {
        x *= n;
        y *= n;
        return *this;
    }

    /**
     * @brief Multiplies the vector by another vector.
     *
     * @param v The Vector to multiply with.
     * @return Vector2& A reference to the updated vector.
     */
    auto operator*=(const Vector2& v) -> Vector2& {
        x *= v.x;
        y *= v.y;
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
    [[nodiscard]] friend bool operator==(const Vector2& a, const Vector2& b) = default;

    /**
     * @brief Subtracts the second vector from the first vector component-wise.
     * @related Vector2
     *
     * @param a The vector to subtract from.
     * @param b The vector to subtract.
     * @return Vector2 A new vector that is the component-wise difference of the two vectors.
     */
    [[nodiscard]] friend auto operator-(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x - b.x, a.y - b.y};
    }

     /**
     * @brief Adds two vectors component-wise.
     * @related Vector2
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Vector2 A new vector that is the component-wise sum of the two vectors.
     */
    [[nodiscard]] friend auto operator+(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x + b.x, a.y + b.y};
    }
};

}