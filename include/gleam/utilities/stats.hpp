/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <memory>

namespace GLEAM_EXPORT gleam {

/**
 * @brief Collects and visualizes runtime performance statistics.
 *
 * The `Stats` class tracks frames per second, frame time, and the number
 * of rendered objects per frame. It is used by the runtime when show_stats
 * is set to true to provide an on-screen performance overlay during development
 * and debugging.
 *
 * Typical usage inside the main loop:
 * @code
 * while (running) {
 *   stats.BeforeRender();
 *   renderer.Render(scene, camera);
 *   stats.AfterRender(renderer.RenderedObjectsPerFrame());
 *   stats.Draw(window.Width());
 * }
 * @endcode
 *
 * @note This overlay requires ImGui support. If the engine is not compiled with
 * `GLEAM_USE_IMGUI`, the `Draw()` method becomes a no-op.
 *
 * @ingroup UtilitiesGroup
 */
class Stats {
public:
    /**
     * @brief Constructs a Stats object.
     */
    Stats();

    /**
     * @brief Marks the beginning of a frame render.
     *
     * Records timing information and increments the frame counter. Call this
     * before issuing any render commands.
     */
    auto BeforeRender() -> void;

    /**
     * @brief Marks the end of a frame render.
     *
     * Updates frame time and records the number of rendered objects.
     *
     * @param n_objects Number of objects rendered in the frame.
     */
    auto AfterRender(unsigned n_objects) -> void;

    /**
     * @brief Draws the performance overlay.
     *
     * Renders a window containing FPS, frame time, and rendered object
     * histograms. The window is positioned in the top-right corner of the
     * application window.
     *
     * @param window_width Logical width of the application window.
     */
    auto Draw(float window_width) const -> void;

    /**
     * @brief Destructor.
     */
    ~Stats();

private:
    /// @cond INTERNAL
    class Impl;
    std::unique_ptr<Impl> impl_;
    /// @endcond
};

}