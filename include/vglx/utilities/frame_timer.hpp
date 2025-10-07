/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/utilities/timer.hpp"

#include <algorithm>

namespace vglx {

/**
 * @brief Frame-oriented helper for computing clamped delta time.
 *
 * `FrameTimer` builds on top of `Timer` to provide a simple, per-frame
 * timestep (`dt`) suitable for driving simulations and animations.
 * Each call to `Tick()` returns the elapsed time since the previous call,
 * clamped by `max_delta` to guard against stalls (e.g., window drags,
 * breakpoints).
 *
 * Typical usage:
 * @code
 * vglx::FrameTimer clock(true); // auto-start
 * while (running) {
 *   const float dt = clock.Tick(); // seconds (float), clamped
 *   scene.Advance(dt);
 *   renderer.Render(&scene, &camera);
 * }
 * @endcode
 *
 * @ingroup UtilitiesGroup
 */
class VGLX_EXPORT FrameTimer {
public:
    /**
     * @brief Constructs a FrameTimer object.
     *
     * @param auto_start If true, the timer starts immediately upon construction.
     */
    explicit FrameTimer(bool auto_start) : timer_(auto_start) {
        if (auto_start) last_ = timer_.GetElapsedSeconds();
    }

    /**
     * @brief Starts the internal timer.
     *
     * Also initializes the internal reference time so the next call to
     * `Tick()` returns the true frame delta.
     */
    auto Start() -> void {
        timer_.Start();
        last_ = timer_.GetElapsedSeconds();
    }

     /**
     * @brief Returns the clamped time delta since the previous tick.
     *
     * Computes the elapsed seconds since the previous `Tick()` (or since
     * `Start()` if this is the first tick) and clamps it to `max_delta`.
     *
     * @param max_delta Maximum allowed delta in seconds (default: 0.1s).
     *
     * @return float
     */
    [[nodiscard]] auto Tick(double max_delta = 0.1) -> float {
        const auto now = timer_.GetElapsedSeconds();
        const auto dt = std::clamp(now - last_, 0.0, max_delta);
        last_ = now;
        return static_cast<float>(dt);
    }

private:
    /// @brief Underlying timer used for timekeeping.
    Timer timer_;

    /// @brief Timestamp of the previous tick, in seconds.
    double last_ {};
};

}