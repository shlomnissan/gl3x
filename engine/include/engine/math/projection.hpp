// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "matrix4.hpp"

namespace engine {

/**
 * @brief Generates an orthographic projection matrix.
 *
 * This function creates a projection matrix for an orthographic projection,
 * which is commonly used for 2D rendering and certain types of 3D rendering
 * where parallel lines remain parallel.
 *
 * @param left The coordinate for the left vertical clipping plane.
 * @param right The coordinate for the right vertical clipping plane.
 * @param bottom The coordinate for the bottom horizontal clipping plane.
 * @param top The coordinate for the top horizontal clipping plane.
 * @param near The distance to the near clipping plane.
 * @param far The distance to the far clipping plane.
 * @return Matrix4 The resulting orthographic projection matrix.
 */
ENGINE_EXPORT
auto ortho(float left, float right, float bottom, float top, float near, float far) -> Matrix4;

/**
 * @brief Generates a perspective projection matrix.
 *
 * This function creates a projection matrix for a perspective projection,
 * which simulates depth and perspective by converging parallel lines towards
 * a vanishing point, commonly used in 3D rendering.
 *
 * @param fov The vertical field of view angle in radians.
 * @param aspect_ratio The aspect ratio of the viewport (width / height).
 * @param near The distance to the near clipping plane.
 * @param far The distance to the far clipping plane.
 * @return Matrix4 The resulting perspective projection matrix.
 */
ENGINE_EXPORT
auto perspective(float fov, float aspect_ratio, float near, float far) -> Matrix4;

}