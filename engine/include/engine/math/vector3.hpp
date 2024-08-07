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
};

inline ENGINE_EXPORT auto Dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline ENGINE_EXPORT auto Cross(const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

};