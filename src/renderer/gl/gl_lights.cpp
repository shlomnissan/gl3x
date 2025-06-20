/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_lights.hpp"

#include "utilities/logger.hpp"

#include <algorithm>

namespace gleam {

auto GLLights::AddLight(Light* light) -> void {
    using enum LightType;

    if (idx_ >= kMaxLights) {
        Logger::Log(
            LogLevel::Error,
            "Exceeded the maximum allowed number of lights ({}) in the scene",
            kMaxLights
        );
        return;
    }

    switch(light->GetType()) {
        case AmbientLight: {
            if (ambient > 0) {
                Logger::Log(
                    LogLevel::Error,
                    "Only one ambient light is permitted per scene."
                );
                return;
            }
            ++ambient;
        }
        break;
        case DirectionalLight: ++directional; break;
        case PointLight: ++point; break;
        case SpotLight: ++spot; break;
    }

    lights_[idx_++] = light;
}

auto GLLights::HasLights() const -> bool {
    return ambient || directional || point || spot;
}

auto GLLights::Reset() -> void {
    std::ranges::fill(lights_, nullptr);
    idx_ = 0;
    ambient = 0;
    directional = 0;
    point = 0;
    spot = 0;
}

}