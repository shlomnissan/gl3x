// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/euler.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/vector3.hpp"

namespace engine {

class ENGINE_EXPORT Transform3D {
public:
    /// @brief Flag indicating if the transformation matrix was modified.
    bool touched {true};

    Transform3D() = default;

    auto Translate(const Vector3& axis, float value) -> void;

    auto Scale(const Vector3& value) -> void;

    auto Rotate(const Vector3& axis, float angle) -> void;

    auto SetPosition(const Vector3& position) -> void;

    auto SetScale(const Vector3& scale) -> void;

    auto SetRotation(const Euler& rotation) -> void;

    [[nodiscard]] auto GetPosition() const { return position_; }

    [[nodiscard]] auto GetScale() const { return scale_; };

    [[nodiscard]] auto GetRotation() const { return rotation_; }

    [[nodiscard]] auto Get() -> Matrix4;

private:
    Matrix4 transform_ {1.0f};

    Vector3 position_ {0.0f};

    Vector3 scale_ {1.0f};

    Euler rotation_ {};
};

}