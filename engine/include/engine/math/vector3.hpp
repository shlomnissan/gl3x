// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

namespace engine {

class ENGINE_EXPORT Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3();

    explicit Vector3(float value);

    Vector3(float x, float y, float z);

    auto length() const -> float;
};

inline ENGINE_EXPORT auto operator+(const Vector3& a, const Vector3& b) {
    return Vector3 {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline ENGINE_EXPORT auto operator-(const Vector3& a, const Vector3& b) {
    return Vector3 {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline ENGINE_EXPORT auto operator*(const Vector3& v, float n) {
    return Vector3 {v.x * n, v.y * n, v.z * n};
}

inline ENGINE_EXPORT auto operator*(float n, const Vector3& v) {
    return v * n;
}

inline ENGINE_EXPORT auto operator/(const Vector3& v, float n) {
    n = 1.0 / n;
    return Vector3 {v.x * n, v.y * n, v.z * n};
}

inline ENGINE_EXPORT auto cross(const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

inline ENGINE_EXPORT auto dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline ENGINE_EXPORT auto normalize(const Vector3& v) {
    const auto len = v.length();
    if (len == 0.0f) {
        return Vector3 {0.0f};
    }
    return v * (1.0f / len);
}

};