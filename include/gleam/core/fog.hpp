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

/**
 * @brief The type of fog.
 */
enum class FogType {
    LinearFog,
    ExponentialFog,
};

struct Fog {
    /// @brief The color of the fog.
    Color color;

    explicit Fog(Color color) : color(color) {}

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
     * @brief Constructs a new LinearFog object.
     *
     * @param color The color of the fog.
     * @param near The distance from the camera where the fog starts.
     * @param far The distance from the camera where the fog ends.
     */
    LinearFog(Color color, float near, float far)
        : Fog(color), near(near), far(far) {}

    /**
     * @brief Retrieves the type of fog.
     *
     * @return The type of fog as `FogType::LinearFog`.
     */
    auto Type() const -> FogType override {
        return FogType::LinearFog;
    }

    /**
     * @brief Creates a new instance of LinearFog.
     *
     * @return A `std::unique_ptr` to a new instance of LinearFog.
     */
    [[nodiscard]] static auto Create(Color color, float near, float far) {
        return std::make_unique<LinearFog>(color, near, far);
    }
};

struct ExponentialFog : public Fog {
    /// @brief The density of the fog.
    float density;

    /**
     * @brief Constructs a new ExponentialFog object.
     *
     * @param color The color of the fog.
     * @param density The density of the fog.
     */
    explicit ExponentialFog(Color color, float density)
        : Fog(color), density(density) {}

    /**
     * @brief Retrieves the type of fog.
     *
     * @return The type of fog as `FogType::ExponentialFog`.
     */
    auto Type() const -> FogType override {
        return FogType::ExponentialFog;
    }

    /**
     * @brief Creates a new instance of ExponentialFog.
     *
     * @return A `std::unique_ptr` to a new instance of ExponentialFog.
     */
    [[nodiscard]] static auto Create(Color color, float density) {
        return std::make_unique<ExponentialFog>(color, density);
    }
};

}