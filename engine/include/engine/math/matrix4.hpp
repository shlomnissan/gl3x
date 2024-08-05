// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "vector4.hpp"

namespace engine {

class ENGINE_EXPORT Matrix4 {
public:
    Matrix4();

    explicit Matrix4(float value);

    Matrix4(
        float n00, float n01, float n02, float n03,
        float n10, float n11, float n12, float n13,
        float n20, float n21, float n22, float n23,
        float n30, float n31, float n32, float n33
    );

    Matrix4(
        const Vector4& a,
        const Vector4& b,
        const Vector4& c,
        const Vector4& d
    );

    auto& operator()(int i, int j) {
        return n[j][i];
    }

    const auto& operator()(int i, int j) const {
        return n[j][i];
    }

    auto& operator[](int j) {
        return (*reinterpret_cast<Vector4*>(n[j]));
    }

    const auto& operator[](int j) const {
        return (*reinterpret_cast<const Vector4*>(n[j]));
    }

private:
    float n[4][4];
};

};