// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "matrix4.hpp"
#include "vector3.hpp"

namespace engine {

ENGINE_EXPORT
auto scale(const Matrix4& m, const Vector3& v) -> Matrix4;

ENGINE_EXPORT
auto rotate(const Matrix4& m, float angle, const Vector3& v) -> Matrix4;

ENGINE_EXPORT
auto translate(const Matrix4& m, const Vector3& v) -> Matrix4;

ENGINE_EXPORT
auto look_at(const Vector3& eye, const Vector3& center, const Vector3& up) -> Matrix4;

}