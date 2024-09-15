// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/matrix4.hpp"

namespace engine {

Matrix4::Matrix4() : Matrix4(0.0f) {}

Matrix4::Matrix4(float value) : Matrix4(
    value, 0.0f, 0.0f, 0.0f,
    0.0f, value, 0.0f, 0.0f,
    0.0f, 0.0f, value, 0.0f,
    0.0f, 0.0f, 0.0f, value
) {}

Matrix4::Matrix4(
    float n00, float n01, float n02, float n03,
    float n10, float n11, float n12, float n13,
    float n20, float n21, float n22, float n23,
    float n30, float n31, float n32, float n33
) : n {
    n00, n10, n20, n30,
    n01, n11, n21, n31,
    n02, n12, n22, n32,
    n03, n13, n23, n33
} {}

Matrix4::Matrix4(
    const Vector4& a,
    const Vector4& b,
    const Vector4& c,
    const Vector4& d
) : n {
    a.x, a.y, a.z, a.w,
    b.x, b.y, b.z, b.w,
    c.x, c.y, c.z, c.w,
    d.x, d.y, d.z, d.w
} {}

}