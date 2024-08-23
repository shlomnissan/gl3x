// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

class ENGINE_EXPORT Transform3D {
public:
    auto Scale(float value) -> void;

    auto Translate(const Vector3& axis, float distance) -> void;

    auto Get() -> Matrix4;

    auto IsDirty() const { return is_dirty_; }

private:
    bool is_dirty_ {true};

    Matrix4 transform_ {1.0f};
    Vector3 position_ {0.0f};
    Vector3 scale_ {1.0f};
};

}