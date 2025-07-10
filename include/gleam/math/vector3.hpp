/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <cassert>
#include <cmath>

namespace gleam {

class Vector3;
auto Dot(const Vector3& a, const Vector3& b) -> float;

class GLEAM_EXPORT Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3() = default;

    Vector3(float value) : Vector3(value, value, value) {}

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    [[nodiscard]] static auto Right() { return Vector3 {1.0f, 0.0f, 0.0f}; }

    [[nodiscard]] static auto Up() { return Vector3 {0.0f, 1.0f, 0.0f}; }

    [[nodiscard]] static auto Forward() { return Vector3 {0.0f, 0.0f, 1.0f}; }

    [[nodiscard]] static auto Zero() { return Vector3 {0.0f}; }

    [[nodiscard]] auto Length() const -> float {
        return std::sqrt(Dot(*this, *this));
    }

    [[nodiscard]] auto LengthSquared() const -> float {
        return Dot(*this, *this);
    }

    auto Normalize() -> Vector3& {
        const auto len = Length();
        return len == 0.0f ? *this : (*this *= (1.0f / len));
    }

    [[nodiscard]] auto& operator[](int i) {
        assert(i >= 0 && i < 3);
        return (reinterpret_cast<float*>(this))[i];
    }

    [[nodiscard]] const auto& operator[](int i) const {
        assert(i >= 0 && i < 3);
        return (reinterpret_cast<const float*>(this))[i];
    }

    auto operator*=(float n) -> Vector3& {
        x *= n;
        y *= n;
        z *= n;
        return *this;
    }

    auto operator*=(const Vector3& v) -> Vector3& {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    auto operator+=(const Vector3& v) -> Vector3& {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    auto operator-=(const Vector3& v) -> Vector3& {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

private:
    [[nodiscard]] friend auto operator==(const Vector3& a, const Vector3& b) -> bool = default;

    [[nodiscard]] friend auto operator+(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    [[nodiscard]] friend auto operator-(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    [[nodiscard]] friend auto operator*(const Vector3& v, float n) {
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }

    [[nodiscard]] friend auto operator*(float n, const Vector3& v) {
        return v * n;
    }

    [[nodiscard]] friend auto operator*(const Vector3& a, const Vector3& b) {
        return Vector3 {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    [[nodiscard]] friend auto operator/(const Vector3& v, float n) {
        n = 1.0f / n;
        return Vector3 {v.x * n, v.y * n, v.z * n};
    }
};

[[nodiscard]] inline auto Cross(const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

[[nodiscard]] inline auto Dot(const Vector3& a, const Vector3& b) -> float {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

[[nodiscard]] inline auto Lerp(const Vector3& v1, const Vector3& v2, float f) {
    return v1 + (v2 - v1) * f;
}

[[nodiscard]] inline auto Normalize(const Vector3& v) {
    const auto len = v.Length();
    if (len == 0.0f) {
        return Vector3::Zero();
    }
    return v * (1.0f / len);
}

}