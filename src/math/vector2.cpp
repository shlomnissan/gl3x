// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/math/vector2.hpp"

namespace engine {

Vector2::Vector2() : Vector2(0.0f) {}

Vector2::Vector2(float value) : Vector2(value, value) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

}