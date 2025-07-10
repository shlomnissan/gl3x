/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <cassert>

namespace gleam {

class GLEAM_EXPORT Vector2 {
public:
    float x;
    float y;

    constexpr Vector2() = default;

    constexpr Vector2(float value) : Vector2(value, value) {}

    constexpr Vector2(float x, float y) : x(x), y(y) {}

    [[nodiscard]] static constexpr auto Zero() { return Vector2 {0.0f}; }

    [[nodiscard]] auto& operator[](int i) {
        assert(i >= 0 && i < 2);
        return (reinterpret_cast<float*>(this))[i];
    }

    [[nodiscard]] const auto& operator[](int i) const {
        assert(i >= 0 && i < 2);
        return (reinterpret_cast<const float*>(this))[i];
    }

    constexpr auto operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    constexpr auto operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    constexpr auto operator*=(float n) {
        x *= n;
        y *= n;
        return *this;
    }

    constexpr auto operator*=(const Vector2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

private:
    [[nodiscard]] friend constexpr auto operator==(const Vector2& a, const Vector2& b) -> bool = default;

    [[nodiscard]] friend constexpr auto operator-(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x - b.x, a.y - b.y};
    }

    [[nodiscard]] friend constexpr auto operator+(const Vector2& a, const Vector2& b) {
        return Vector2 {a.x + b.x, a.y + b.y};
    }
};

}