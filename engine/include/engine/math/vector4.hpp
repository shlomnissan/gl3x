// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

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
};

inline auto Dot(const Vector4& a, const Vector4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

};