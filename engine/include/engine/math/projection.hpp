// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "matrix4.hpp"

namespace engine {

ENGINE_EXPORT
auto ortho(float left, float right, float bottom, float top, float near, float far) -> Matrix4;

ENGINE_EXPORT
auto perspective(float fov, float aspect_ratio, float near, float far) -> Matrix4;

}