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

class Vector4;
auto Dot(const Vector4& a, const Vector4& b) -> float;

class GLEAM_EXPORT Vector4 {
public:
    float x;
    float y;
    float z;
    float w;

    Vector4() = default;

    Vector4(float value) : Vector4(value, value, value, value) {}

    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    [[nodiscard]] static auto Zero() { return Vector4 {0.0f}; }

    [[nodiscard]] auto Length() const -> float {
        return std::sqrt(Dot(*this, *this));
    }

    [[nodiscard]] auto LengthSquared() const -> float {
        return Dot(*this, *this);
    }

    auto Normalize() -> Vector4& {
        const auto len = Length();
        return len == 0.0f ? *this : (*this *= (1.0f / len));
    }

    [[nodiscard]] auto& operator[](int i) {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<float*>(this))[i];
    }

    [[nodiscard]] const auto& operator[](int i) const {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<const float*>(this))[i];
    }

    auto operator*=(float n) -> Vector4& {
        x *= n;
        y *= n;
        z *= n;
        w *= n;
        return *this;
    }

    auto operator*=(const Vector4& v) -> Vector4& {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    auto operator+=(const Vector4& v) -> Vector4& {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    auto operator-=(const Vector4& v) -> Vector4& {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

private:
    [[nodiscard]] friend auto operator==(const Vector4& a, const Vector4& b) -> bool = default;

    [[nodiscard]] friend auto operator+(const Vector4& a, const Vector4& b) {
        return Vector4 {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    }

    [[nodiscard]] friend auto operator-(const Vector4& a, const Vector4& b) {
        return Vector4 {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    }

    [[nodiscard]] friend auto operator*(const Vector4& v, float n) {
        return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
    }

    [[nodiscard]] friend auto operator*(float n, const Vector4& v) {
        return v * n;
    }

    [[nodiscard]] friend auto operator*(const Vector4& a, const Vector4& b) {
        return Vector4 {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    [[nodiscard]] friend auto operator/(const Vector4& v, float n) {
        n = 1.0f / n;
        return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
    }
};

[[nodiscard]] inline auto Dot(const Vector4& a, const Vector4& b) -> float {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

[[nodiscard]] inline auto Lerp(const Vector4& v1, const Vector4& v2, float f) {
    return v1 + (v2 - v1) * f;
}

[[nodiscard]] inline auto Normalize(const Vector4& v) {
    const auto len = v.Length();
    if (len == 0.0f) {
        return Vector4::Zero();
    }
    return v * (1.0f / len);
}

}