// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/matrix3.hpp>

using namespace engine;

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
) {
    n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
    n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
    n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
}

Matrix3::Matrix3(
    const Vector3& a,
    const Vector3& b,
    const Vector3& c
) {
    n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
    n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
    n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
}