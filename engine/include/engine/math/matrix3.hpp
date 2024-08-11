// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "vector3.hpp"

namespace engine {

class ENGINE_EXPORT Matrix3 {
public:
    Matrix3();

    explicit Matrix3(float value);

    Matrix3(
        float n00, float n01, float n02,
        float n10, float n11, float n12,
        float n20, float n21, float n22
    );

    Matrix3(
        const Vector3& a,
        const Vector3& b,
        const Vector3& c
    );

    auto& operator()(int i, int j) {
        return n[j][i];
    }

    const auto& operator()(int i, int j) const {
        return n[j][i];
    }

    auto& operator[](int j) {
        return (*reinterpret_cast<Vector3*>(n[j]));
    }

    const auto& operator[](int j) const {
        return (*reinterpret_cast<const Vector3*>(n[j]));
    }

private:
    float n[3][3];
};

inline ENGINE_EXPORT auto operator*(const Matrix3& a, const Matrix3& b) {
    return Matrix3 {
       a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
       a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
       a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),
       a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
       a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
       a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),
       a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
       a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
       a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2),
    };
}

};