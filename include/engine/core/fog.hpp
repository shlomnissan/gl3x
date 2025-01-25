// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/math/color.hpp"

namespace engine {

/**
 * @brief The type of fog.
 */
enum class FogType {
    LinearFog,
    ExponentialFog,
};

struct Fog {
    /// @brief The color of the fog.
    Color color {0.0f, 0.0f, 0.0f};

     /**
     * @brief Retrieves the type of fog.
     *
     * @return The type of fog.
     */
    [[nodiscard]] virtual auto Type() const -> FogType = 0;

    /**
     * @brief Default destructor.
     */
    virtual ~Fog() = default;
};

struct LinearFog : public Fog {
    /// @brief The distance from the camera where the fog starts.
    float near;

    /// @brief The distance from the camera where the fog ends.
    float far;

    /**
     * @brief Retrieves the type of fog.
     *
     * @return The type of fog as `FogType::LinearFog`.
     */
    auto Type() const -> FogType override {
        return FogType::LinearFog;
    }
};

struct ExponentialFog : public Fog {
    /// @brief The density of the fog.
    float density;

    /**
     * @brief Retrieves the type of fog.
     *
     * @return The type of fog as `FogType::ExponentialFog`.
     */
    auto Type() const -> FogType override {
        return FogType::ExponentialFog;
    }
};

}