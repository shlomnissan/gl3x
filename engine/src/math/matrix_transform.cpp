// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/matrix_transform.hpp>

namespace engine {

auto scale(const Matrix4& m, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {1.0f};
    return output;
}

auto rotate(const Matrix4& m, float angle, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {1.0f};
    return output;
}

auto translate(const Matrix4& m, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {1.0f};
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