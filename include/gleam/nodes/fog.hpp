/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/math/color.hpp"

#include <memory>

namespace gleam {

enum class FogType {
    LinearFog,
    ExponentialFog,
};

struct Fog {
    Color color;

    explicit Fog(Color color) : color(color) {}

    [[nodiscard]] virtual auto GetType() const -> FogType = 0;

    virtual ~Fog() = default;
};

struct LinearFog : public Fog {
    float near;
    float far;

    LinearFog(Color color, float near, float far)
        : Fog(color), near(near), far(far) {}

    auto GetType() const -> FogType override {
        return FogType::LinearFog;
    }

    [[nodiscard]] static auto Create(Color color, float near, float far) {
        return std::make_unique<LinearFog>(color, near, far);
    }
};

struct ExponentialFog : public Fog {
    float density;

    explicit ExponentialFog(Color color, float density)
        : Fog(color), density(density) {}

    auto GetType() const -> FogType override {
        return FogType::ExponentialFog;
    }

    [[nodiscard]] static auto Create(Color color, float density) {
        return std::make_unique<ExponentialFog>(color, density);
    }
};

}