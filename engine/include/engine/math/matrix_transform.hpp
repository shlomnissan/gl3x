// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "matrix4.hpp"
#include "vector3.hpp"

namespace engine {

auto Scale(const Matrix4& m, const Vector3& v) -> Matrix4;

auto Rotate(const Matrix4& m, float angle, const Vector3& v) -> Matrix4;

auto Translate(const Matrix4& m, const Vector3& v) -> Matrix4;

auto LookAt(const Vector3& eye, const Vector3& target, const Vector3& up) -> Matrix4;

}