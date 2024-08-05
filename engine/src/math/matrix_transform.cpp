// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/matrix_transform.hpp>

namespace engine {

auto Scale(const Matrix4& m, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {1.0f};
    return output;
}

auto Rotate(const Matrix4& m, float angle, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {1.0f};
    return output;
}

auto Translate(const Matrix4& m, const Vector3& v) -> Matrix4 {
    auto output = Matrix4 {1.0f};
    return output;
}

auto LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) -> Matrix4 {
    auto output = Matrix4 {};
    return output;
}

}