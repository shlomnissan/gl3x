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

class Vector2;
auto constexpr Dot(const Vector2& a, const Vector2& b) -> float;

class GLEAM_EXPORT Vector2 {
public:
    float x;
    float y;

    constexpr Vector2() = default;

    constexpr Vector2(float value) : Vector2(value, value) {}

    constexpr Vector2(float x, float y) : x(x), y(y) {}

    [[nodiscard]] static constexpr auto Right() { return Vector2 {1.0f, 0.0f}; }

    [[nodiscard]] static constexpr auto Up() { return Vector2 {0.0f, 1.0f}; }

    [[nodiscard]] static constexpr auto Zero() { return Vector2 {0.0f}; }

    [[nodiscard]] constexpr auto Length() const { return math::Sqrt(Dot(*this, *this)); }

    [[nodiscard]] constexpr auto LengthSquared() const { return Dot(*this, *this); }

    [[nodiscard]] auto& operator[](int i) {
        assert(i >= 0 && i < 2);
        return (reinterpret_cast<float*>(this))[i];
    }

    [[nodiscard]] const auto& operator[](int i) const {
        assert(i >= 0 && i < 2);
        return (reinterpret_cast<const float*>(this))[i];
    }

    constexpr auto Normalize() -> Vector2& {
        const auto len = Length();
        return len == 0.0f ? *this : (*this *= (1.0f / len));
    }

    constexpr auto operator+=(const Vector2& v) -> Vector2& {
        x += v.x;
        y += v.y;
        return *this;
    }

    constexpr auto operator-=(const Vector2& v) -> Vector2& {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    constexpr auto operator*=(float n) -> Vector2& {
        x *= n;
        y *= n;
        return *this;
    }

    constexpr auto operator*=(const Vector2& v) -> Vector2& {
        x *= v.x;
        y *= v.y;
        return *this;
    }

private:
    [[nodiscard]] friend constexpr auto operator==(const Vector2& a, const Vector2& b) -> bool = default;

    [[nodiscard]] friend constexpr auto operator+(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x + b.x, a.y + b.y};
    }

    [[nodiscard]] friend constexpr auto operator-(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x - b.x, a.y - b.y};
    }

    [[nodiscard]] friend constexpr auto operator*(const Vector2& v, float n) {
        return Vector2 {v.x * n, v.y * n};
    }

    [[nodiscard]] friend constexpr auto operator*(float n, const Vector2& v) {
        return v * n;
    }

    [[nodiscard]] friend constexpr auto operator*(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x * b.x, a.y * b.y};
    }

    [[nodiscard]] friend constexpr auto operator/(const Vector2& v, float n) {
        n = 1.0f / n;
        return Vector2 {v.x * n, v.y * n};
    }
};

[[nodiscard]] inline constexpr auto Dot(const Vector2& a, const Vector2& b) -> float {
    return a.x * b.x + a.y * b.y;
}

[[nodiscard]] inline constexpr auto Lerp(const Vector2& v1, const Vector2& v2, float f) {
    return v1 + (v2 - v1) * f;
}

[[nodiscard]] inline constexpr auto Normalize(const Vector2& v) {
    const auto len = v.Length();
    return len == 0.0f ? Vector2::Zero() : v * (1.0f / len);
}

}