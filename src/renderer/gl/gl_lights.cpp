/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#include "renderer/gl/gl_lights.hpp"

#include "gl3x/lights/directional_light.hpp"
#include "gl3x/lights/point_light.hpp"
#include "gl3x/lights/spot_light.hpp"
#include "gl3x/math/utilities.hpp"

#include "utilities/logger.hpp"

#include <algorithm>

namespace gl3x {

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
        ambient_light = light->color * light->intensity;
        ++ambient;
    } else {
        auto& dst = lights_.lights[idx_++];
        dst.type = static_cast<unsigned>(light->GetType());
        dst.color = light->color * light->intensity;

        switch(light->GetType()) {
            case AmbientLight: /* noop */ break;
            case DirectionalLight: {
                ++directional;
                auto src = static_cast<gl3x::DirectionalLight*>(light);
                auto src_dir = src->Direction();
                auto dir = camera->view_matrix * Vector4(src_dir.x, src_dir.y, src_dir.z, 0.0f);
                dst.position = Vector3::Zero();
                dst.direction = Vector3(dir.x, dir.y, dir.z);
                dst.cone_cos = 0.0f;
                dst.penumbra_cos = 0.0f;
                dst.base = 0.0f;
                dst.linear = 0.0f;
                dst.quadratic = 0.0f;
            }
            break;
            case PointLight: {
                ++point;
                auto src = static_cast<gl3x::PointLight*>(light);
                auto world = src->GetWorldPosition();
                auto pos = camera->view_matrix *  Vector4(world.x, world.y, world.z, 1.0f);
                dst.position = Vector3(pos.x, pos.y, pos.z);
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
                auto src = static_cast<gl3x::SpotLight*>(light);
                auto src_dir = src->Direction();
                auto world = src->GetWorldPosition();
                auto dir = camera->view_matrix * Vector4(src_dir.x, src_dir.y, src_dir.z, 0.0f);
                auto pos = camera->view_matrix * Vector4(world.x, world.y, world.z, 1.0f);
                dst.position = Vector3(pos.x, pos.y, pos.z);
                dst.direction = Vector3(dir.x, dir.y, dir.z);
                dst.cone_cos = math::Cos(src->angle);
                dst.penumbra_cos = math::Cos(src->angle * (1 - src->penumbra));
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