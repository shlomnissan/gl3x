// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "matrix4.hpp"
#include "vector3.hpp"

namespace engine {

/**
 * @brief Scales a matrix by a given vector.
 *
 * This function applies a scaling transformation to the matrix `m` using the
 * scaling factors provided in the vector `v`.
 *
 * @param m The matrix to be scaled.
 * @param v The scaling factors along each axis.
 * @return Matrix4 The resulting matrix after scaling.
 */
[[nodiscard]] ENGINE_EXPORT
auto Scale(const Matrix4& m, const Vector3& v) -> Matrix4;

/**
 * @brief Scales a matrix uniformly by a given value.
 *
 * This function applies a uniform scaling transformation to the matrix `m`
 * using the provided scalar value `value`.
 *
 * @param m The matrix to be scaled.
 * @param value The uniform scaling factor.
 * @return Matrix4 The resulting matrix after uniform scaling.
 */
[[nodiscard]] ENGINE_EXPORT
auto Scale(const Matrix4& m, const float value) -> Matrix4;

/**
 * @brief Rotates a matrix by a given angle around a specified axis.
 *
 * This function applies a rotation transformation to the matrix `m` around the
 * axis defined by vector `v` by the angle `angle`.
 *
 * @param m The matrix to be rotated.
 * @param angle The angle of rotation in radians.
 * @param v The axis of rotation.
 * @return Matrix4 The resulting matrix after rotation.
 */
[[nodiscard]] ENGINE_EXPORT
auto Rotate(const Matrix4& m, float angle, const Vector3& v) -> Matrix4;

/**
 * @brief Translates a matrix by a given vector.
 *
 * This function applies a translation transformation to the matrix `m` using
 * the translation vector `v`.
 *
 * @param m The matrix to be translated.
 * @param v The translation vector.
 * @return Matrix4 The resulting matrix after translation.
 */
[[nodiscard]] ENGINE_EXPORT
auto Translate(const Matrix4& m, const Vector3& v) -> Matrix4;

/**
 * @brief Creates a view matrix for a camera with a specified position, target, and up direction.
 *
 * This function generates a view matrix for the camera based on the `eye`
 * (camera position), `center` (target position),  and `up` (upward direction)
 * vectors. This matrix is commonly used to set up a view or camera transformation in 3D space.
 *
 * @param eye The position of the camera.
 * @param center The point the camera is looking at.
 * @param up The direction that points upwards relative to the camera.
 * @return Matrix4 The resulting view matrix.
 */
[[nodiscard]] ENGINE_EXPORT
auto LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) -> Matrix4;

}