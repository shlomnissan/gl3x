// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "engine/lights/directional_light.hpp"

namespace engine {

auto DirectionalLight::SetDebugMode(bool enabled) -> void {
    debug_mode = enabled;
    if (debug_mode && Children().empty()) {
        CreateDebugMesh();
    }
}

auto DirectionalLight::CreateDebugMesh() -> void {
    // TODO: add
}

}