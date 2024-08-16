// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <cassert>

namespace engine {

class ENGINE_EXPORT Vector4 {
public:
    float x;
    float y;
    float z;
    float w;

    Vector4();

    explicit Vector4(float value);

    Vector4(float x, float y, float z, float w);

    auto length() const -> float;

    auto& operator[](int i) {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<float*>(this))[i];
    }

    const auto& operator[](int i) const {
        assert(i >= 0 && i < 4);
        return (reinterpret_cast<const float*>(this))[i];
    }
};

inline ENGINE_EXPORT
auto operator+(const Vector4& a, const Vector4& b) {
    return Vector4 {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

inline ENGINE_EXPORT
auto operator-(const Vector4& a, const Vector4& b) {
    return Vector4 {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

inline ENGINE_EXPORT
auto operator*(const Vector4& v, float n) {
    return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
}

inline ENGINE_EXPORT
auto operator*(float n, const Vector4& v) {
    return v * n;
}

inline ENGINE_EXPORT
auto operator/(const Vector4& v, float n) {
    n = 1.0 / n;
    return Vector4 {v.x * n, v.y * n, v.z * n, v.w * n};
}

inline ENGINE_EXPORT
auto dot(const Vector4& a, const Vector4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline ENGINE_EXPORT
auto normalize(const Vector4& v) {
    const auto len = v.length();
    if (len == 0.0f) {
        return Vector4 {0.0f};
    }
    return v * (1.0f / len);
}

};