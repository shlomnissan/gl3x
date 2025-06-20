/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam/lights/light.hpp"

#include <array>

namespace gleam {

class GLLights {
public:
    static constexpr auto kMaxLights = 10;

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

    auto AddLight(Light* light) -> void;

    auto HasLights() const -> bool;

    auto Reset() -> void;

    const auto& Lights() const { return lights_; }

private:
    std::array<Light*, kMaxLights> lights_ {};

    unsigned int idx_ {0};
};

}