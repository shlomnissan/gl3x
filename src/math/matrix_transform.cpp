// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/matrix_transform.hpp>

#include <cmath>

namespace engine {

auto scale(const Matrix4& m, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {};
    output[0] = m[0] * v[0];
    output[1] = m[1] * v[1];
    output[2] = m[2] * v[2];
    output[3] = m[3];
    return output;
}

auto scale(const Matrix4& m, const float value) -> Matrix4 {
    return scale(m, Vector3 {value});
}

auto rotate(const Matrix4& m, float angle, const Vector3& v) -> Matrix4 {
    const auto a = angle;
    const auto c = std::cos(a);
    const auto s = std::sin(a);
    const auto axis = normalize(v);
    const auto temp = (1.0f - c) * axis;

    auto rotate = engine::Matrix4 {};
    rotate[0] = {
        c + temp[0] * axis[0],
        temp[0] * axis[1] + s * axis[2],
        temp[0] * axis[2] - s * axis[1],
        0.0f
    };
    rotate[1] = {
        temp[1] * axis[0] - s * axis[2],
        c + temp[1] * axis[1],
        temp[1] * axis[2] + s * axis[0],
        0.0f
    };
    rotate[2] = {
        temp[2] * axis[0] + s * axis[1],
        temp[2] * axis[1] - s * axis[0],
        c + temp[2] * axis[2],
        0.0f
    };

    auto output = engine::Matrix4 {};
    output[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
    output[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
    output[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
    output[3] = m[3];
    return output;
}

auto translate(const Matrix4& m, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {m};
    output[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
    return output;
}

auto look_at(const Vector3& eye, const Vector3& center, const Vector3& up) -> Matrix4 {
    const auto f = normalize(center - eye);
    const auto s = normalize(cross(f, up));
    const auto u  = cross(s, f);
    return Matrix4 {
         s.x,  s.y,  s.z, -dot(s, eye),
         u.x,  u.y,  u.z, -dot(u, eye),
        -f.x, -f.y, -f.z,  dot(f, eye),
         0,    0,    0,    1.0f
    };
}

}