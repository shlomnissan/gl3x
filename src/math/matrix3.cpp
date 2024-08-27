// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/matrix3.hpp>

namespace engine {

Matrix3::Matrix3() : Matrix3(0.0f) {}

Matrix3::Matrix3(float value) : Matrix3(
    value, 0.0f, 0.0f,
    0.0f, value, 0.0f,
    0.0f, 0.0f, value
) {}

Matrix3::Matrix3(
    float n00, float n01, float n02,
    float n10, float n11, float n12,
    float n20, float n21, float n22
) : n {
    n00, n10, n20, n01, n11, n21, n02, n12, n22
} {}

Matrix3::Matrix3(
    const Vector3& a,
    const Vector3& b,
    const Vector3& c
) : n {
    a.x, a.y, a.z,
    b.x, b.y, b.z,
    c.x, c.y, c.z
} {}

}