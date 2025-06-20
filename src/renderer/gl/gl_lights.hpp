/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/lights/light.hpp"

#include "gleam/cameras/camera.hpp"
#include "gleam/math/color.hpp"
#include "gleam/math/vector3.hpp"

#include "renderer/gl/gl_uniform_buffer.hpp"

#include <array>

namespace gleam {

class GLLights {
public:
    static constexpr auto kMaxLights = 10;

    struct alignas(16) UniformLight {
        alignas(4)  int type {0};
        alignas(16) Color color {0xFFFFFF};
        alignas(16) Vector3 position {Vector3::Zero()};
        alignas(16) Vector3 direction {Vector3::Zero()};
        alignas(4)  float cone_cos {0.0f};
        alignas(4)  float penumbra_cos {0.0f};
        alignas(4)  float base {0.0f};
        alignas(4)  float linear {0.0f};
        alignas(4)  float quadratic {0.0f};
    };

    struct alignas(16) UniformLights {
        alignas(16) UniformLight lights[kMaxLights];
    };

    unsigned int ambient {0};
    unsigned int directional {0};
    unsigned int point {0};
    unsigned int spot {0};

    GLLights() = default;

    // delete move constructor and assignment operator
    GLLights(GLLights&&) = delete;
    auto operator=(GLLights&&) -> GLLights& = delete;

    // delete copy constructor and assignment operator
    GLLights(const GLLights&) = delete;
    auto operator=(const GLLights&) -> GLLights& = delete;

    auto AddLight(Light* light, Camera* camera) -> void;

    auto AmbientLight() const { return ambient_; }

    auto HasLights() const -> bool;

    auto Reset() -> void;

    auto Update() -> void;

private:
    UniformLights lights_ {};

    GLUniformBuffer uniform_buffer_ {"ub_Lights", sizeof(UniformLights)};

    Color ambient_ {0x000000};

    unsigned int idx_ {0};
};

}