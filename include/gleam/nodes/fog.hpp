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
 * @brief Represents available fog types.
 * @ingroup NodesGroup
 */
enum class FogType {
    LinearFog,
    ExponentialFog,
};

/**
 * @internal
 * @brief Abstract base class for fog types.
 *
 * Not intended for direct use.
 *
 * @ingroup NodesGroup
 */
struct Fog {
    Color color;

    explicit Fog(Color color) : color(color) {}

    [[nodiscard]] virtual auto GetType() const -> FogType = 0;

    virtual ~Fog() = default;
};

/**
 * @brief Linearly interpolated fog effect, assignable to a scene.
 *
 * This fog model applies a linear blend between no fog and full fog color
 * based on fragment distance. It is intended to be assigned to a `Scene`'s
 * `fog` field at runtime.
 *
 * @code
 * my_scene->fog = gleam::LinearFog::Create(0x444444, 2.0f, 6.0f);
 * @endcode
 *
 * @ingroup NodesGroup
 */
struct LinearFog : public Fog {
    /// @brief Distance at which fog starts.
    float near;
    /// @brief Distance at which fog reaches full opacity.
    float far;

    /**
     * @brief Constructs a LinearFog object.
     *
     * @param color Fog color.
     * @param near Start distance of the fog effect.
     * @param far End distance of the fog effect.
     */
    LinearFog(Color color, float near, float far)
        : Fog(color), near(near), far(far) {}

    /**
     * @brief Creates a shared pointer to a LinearFog object.
     *
     * @param color Fog color.
     * @param near Start distance of the fog effect.
     * @param far End distance of the fog effect.
     * @return std::shared_ptr<LinearFog>
     */
    [[nodiscard]] static auto Create(Color color, float near, float far) {
        return std::make_unique<LinearFog>(color, near, far);
    }

    /**
     * @brief Returns fog type.
     *
     * @return FogType::LinearFog
     */
    auto GetType() const -> FogType override {
        return FogType::LinearFog;
    }
};

/**
 * @brief Exponential fog effect, assignable to a scene.
 *
 * This fog model uses an exponential function based on view distance
 * to simulate atmospheric fading. It is intended to be assigned to a
 * `Scene`'s `fog` field at runtime.
 *
 * @code
 * my_scene->fog = gleam::ExponentialFog::Create(0x888888, 0.15f);
 * @endcode
 *
 * @ingroup NodesGroup
 */
struct ExponentialFog : public Fog {
    /// @brief Density factor controlling fog steepness.
    float density;

    /**
     * @brief Constructs an ExponentialFog object.
     *
     * @param color Fog color.
     * @param density Density factor.
     */
    explicit ExponentialFog(Color color, float density)
        : Fog(color), density(density) {}

    /**
     * @brief Creates a shared pointer to an ExponentialFog object.
     *
     * @param color Fog color.
     * @param density Density factor.
     * @return std::shared_ptr<ExponentialFog>
     */
    [[nodiscard]] static auto Create(Color color, float density) {
        return std::make_unique<ExponentialFog>(color, density);
    }

    /**
     * @brief Returns fog type.
     *
     * @return FogType::ExponentialFog
     */
    auto GetType() const -> FogType override {
        return FogType::ExponentialFog;
    }
};

}