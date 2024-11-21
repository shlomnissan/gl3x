// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include "engine/math/color.hpp"
#include "engine/scene/mesh.hpp"
#include "engine/scene/node.hpp"

#include <memory>
#include <optional>

namespace engine {

enum class LightType {
    Ambient,
    Directional,
    Point,
    Spotlight
};

class ENGINE_EXPORT Light : public Node {
public:
    Color color;

    float intensity;

    bool debug_mode {false};

    Light(Color color = {0xffffff}, float intensity = 1.0f)
        : color(color), intensity(intensity) {}

    [[nodiscard]] virtual auto Type() const -> LightType = 0;

    virtual auto SetDebugMode(bool enabled) -> void {
        debug_mode = enabled;
        if (!debug_mode) {
            RemoveAllChildren();
        }
    }

    ~Light() override = default;
};

}