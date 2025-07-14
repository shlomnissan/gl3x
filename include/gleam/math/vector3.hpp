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

class GLEAM_EXPORT Vector3 {
public:
    float x;
    float y;
    float z;

    constexpr Vector3() = default;

    constexpr Vector3(float value) : Vector3(value, value, value) {}

    constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    [[nodiscard]] static constexpr auto Forward() { return Vector3 {0.0f, 0.0f, 1.0f}; }

    [[nodiscard]] static constexpr auto Right() { return Vector3 {1.0f, 0.0f, 0.0f}; }

    [[nodiscard]] static constexpr auto Up() { return Vector3 {0.0f, 1.0f, 0.0f}; }

    [[nodiscard]] static constexpr auto Zero() { return Vector3 {0.0f}; }

    [[nodiscard]] constexpr auto Length() const { return math::Sqrt(Dot(*this, *this)); }

    [[nodiscard]] constexpr auto LengthSquared() const { return Dot(*this, *this); }

    [[nodiscard]] constexpr auto& operator[](int i) {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return x; // placeholder
        }
    }

    [[nodiscard]] constexpr auto& operator[](int i) const {
        assert(i >= 0 && i < 3);
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return x; // placeholder
        }
    }

    constexpr auto Normalize() -> Vector3& {
        const auto len = Length();
        return len == 0.0f ? *this : (*this *= (1.0f / len));
    }

    constexpr auto operator+=(const Vector3& v) -> Vector3& {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr auto operator-=(const Vector3& v) -> Vector3& {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr auto operator*=(float n) -> Vector3& {
        x *= n;
        y *= n;
        z *= n;
        return *this;
    }

    constexpr auto operator*=(const Vector3& v) -> Vector3& {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

private:
    [[nodiscard]] friend constexpr auto operator==(const Vector3& a, const Vector3& b) -> bool = default;

    [[nodiscard]] friend constexpr auto operator+(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    [[nodiscard]] friend constexpr auto operator-(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    [[nodiscard]] friend constexpr auto operator*(const Vector3& v, float n) {
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }

    [[nodiscard]] friend constexpr auto operator*(float n, const Vector3& v) {
        return v * n;
    }

    [[nodiscard]] friend constexpr auto operator*(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    [[nodiscard]] friend constexpr auto operator/(const Vector3& v, float n) {
        n = 1.0f / n;
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }
};

[[nodiscard]] inline constexpr auto Cross(const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

[[nodiscard]] inline constexpr auto Dot(const Vector3& a, const Vector3& b) -> float {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

[[nodiscard]] inline constexpr auto Lerp(const Vector3& v1, const Vector3& v2, float f) {
    return v1 + (v2 - v1) * f;
}

[[nodiscard]] inline constexpr auto Normalize(const Vector3& v) {
    const auto len = v.Length();
    return len == 0.0f ? Vector3::Zero() : v * (1.0f / len);
}

}