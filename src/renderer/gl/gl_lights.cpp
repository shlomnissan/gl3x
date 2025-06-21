/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_lights.hpp"

#include "gleam/lights/directional_light.hpp"
#include "gleam/lights/point_light.hpp"
#include "gleam/lights/spot_light.hpp"

#include "utilities/logger.hpp"

#include <algorithm>
#include <cmath>

namespace gleam {

auto GLLights::AddLight(Light* light, Camera* camera) -> void {
    using enum LightType;

    if (idx_ >= kMaxLights) {
        Logger::Log(
            LogLevel::Error,
            "Exceeded the maximum allowed number of lights ({}) in the scene",
            kMaxLights
        );
        return;
    }

    if (light->GetType() == AmbientLight) {
        if (ambient >= 1) {
            Logger::Log(
                LogLevel::Error,
                "Only one ambient light is permitted per scene."
            );
            return;
        }
        ambient_ = light->color * light->intensity;
        ++ambient;
    } else {
        auto& dst = lights_.lights[idx_++];
        dst.type = static_cast<unsigned>(light->GetType());
        dst.color = light->color * light->intensity;

        switch(light->GetType()) {
            case AmbientLight: /* noop */ break;
            case DirectionalLight: {
                ++directional;
                auto src = static_cast<gleam::DirectionalLight*>(light);
                dst.position = Vector3::Zero();
                dst.direction = Vector3(camera->view_transform * Vector4(src->Direction(), 0.0f));
                dst.cone_cos = 0.0f;
                dst.penumbra_cos = 0.0f;
                dst.base = 0.0f;
                dst.linear = 0.0f;
                dst.quadratic = 0.0f;
            }
            break;
            case PointLight: {
                ++point;
                auto src = static_cast<gleam::PointLight*>(light);
                dst.position = Vector3(camera->view_transform * Vector4(src->GetWorldPosition(), 1.0f));
                dst.direction = Vector3::Zero();
                dst.cone_cos = 0.0f;
                dst.penumbra_cos = 0.0f;
                dst.base = src->attenuation.base;
                dst.linear = src->attenuation.linear;
                dst.quadratic = src->attenuation.quadratic;
            }
            break;
            case SpotLight: {
                ++spot;
                auto src = static_cast<gleam::SpotLight*>(light);
                dst.position = Vector3(camera->view_transform * Vector4(src->GetWorldPosition(), 1.0f));
                dst.direction = Vector3(camera->view_transform * Vector4(src->Direction(), 0.0f));
                dst.cone_cos = std::cos(src->angle);
                dst.penumbra_cos = std::cos(src->angle * (1 - src->penumbra));
                dst.base = src->attenuation.base;
                dst.linear = src->attenuation.linear;
                dst.quadratic = src->attenuation.quadratic;
            }
            break;
        };
    }
}

auto GLLights::Update() -> void {
    uniform_buffer_.UploadIfNeeded(&lights_, sizeof(lights_));
}

auto GLLights::HasLights() const -> bool {
    return ambient || directional || point || spot;
}

auto GLLights::Reset() -> void {
    idx_ = 0;
    ambient = 0;
    directional = 0;
    point = 0;
    spot = 0;
}

}