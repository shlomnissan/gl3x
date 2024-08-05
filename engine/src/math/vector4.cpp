// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <engine/math/vector4.hpp>

using namespace engine;

Vector4::Vector4() : Vector4(0.0) {}

Vector4::Vector4(float value) : Vector4(value, value, value, value) {}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}