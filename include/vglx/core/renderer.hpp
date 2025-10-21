/*
===========================================================================
  VGLX https://vglx.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "vglx_export.h"

#include "vglx/cameras/camera.hpp"
#include "vglx/math/color.hpp"
#include "vglx/nodes/scene.hpp"

#include <memory>
#include <string>

namespace vglx {

/**
 * @brief Forward renderer for drawing a scene from a given camera.
 *
 * The @ref Renderer owns GPU state and draw logic for rendering a @ref Scene with a
 * specified @ref Camera. It is typically constructed and driven by the
 * @ref Application runtime, but can also be used directly in manual setups.
 *
 * @code
 * vglx::Renderer renderer({
 *   .framebuffer_width = window.FramebufferWidth(),
 *   .framebuffer_height = window.FramebufferHeight(),
 *   .clear_color = 0x444444
 * });
 *
 * auto ok = renderer.Initialize();
 * if (!ok) {
 *   HandleError(ok.error());
 * }
 *
 * // Per-frame:
 * renderer.Render(scene.get(), camera.get());
 * @endcode
 *
 * @note The renderer assumes a valid graphics context is current on the
 * calling thread. When the window is resized, call @ref SetViewport to adjust
 * the render area (or recreate with new parameters if you manage your own
 * framebuffers).
 *
 * @ingroup CoreGroup
 */
class VGLX_EXPORT Renderer {
public:
    /// @brief Parameters for constructing a Renderer object.
    struct Parameters {
        int framebuffer_width; ///< Current framebuffer width in pixels.
        int framebuffer_height; ///< Current framebuffer height in pixels.
        Color clear_color; ///< Clear color used at the start of a frame.
    };

    /**
     * @brief Constructs a Renderer object.
     *
     * GPU resources are not created until @ref Initialize is called.
     *
     * @param params @ref Renderer::Parameters "Initialization parameters"
     * for constructing the renderer.
     */
    explicit Renderer(const Renderer::Parameters& params);

    // Non-copyable
    Renderer(const Renderer&) = delete;
    auto operator=(const Renderer&) -> Renderer& = delete;

    // Movable
    Renderer(Renderer&&) noexcept = default;
    auto operator=(Renderer&&) noexcept -> Renderer& = default;

    /**
     * @brief Initializes GPU state and allocates required resources.
     */
    [[nodiscard]] auto Initialize() -> std::expected<void, std::string>;

    /**
     * @brief Renders the given scene from the specified camera.
     *
     * The scene is expected to be in a consistent state for rendering.
     * If you are using the runtime path, this is handled automatically.
     * In direct initialization flows, call your per-frame update routine
     * (e.g., @ref Scene::Advance) prior to rendering.
     *
     * @param scene Pointer to the scene to render (must be non-null).
     * @param camera Pointer to the active camera (must be non-null).
     */
    auto Render(Scene* scene, Camera* camera) -> void;

    /**
     * @brief Sets the active viewport rectangle in pixels.
     *
     * Adjusts the area of the framebuffer that subsequent draw calls will target.
     * This should be called whenever the window or framebuffer size changes, or
     * when rendering to a specific sub-region of the target surface.
     *
     * When using the runtime-managed rendering path, the viewport is updated
     * automatically. In manual initialization flows, you are responsible for
     * calling this method whenever the framebuffer dimensions change.
     *
     * @param x Left pixel of the viewport.
     * @param y Bottom pixel of the viewport.
     * @param width Viewport width in pixels.
     * @param height Viewport height in pixels.
     */
    auto SetViewport(int x, int y, int width, int height) -> void;

    /**
     * @brief Sets the clear color for subsequent frames.
     *
     * The color is applied at the start of each frame when the framebuffer
     * is cleared. Typically used to define the background color of the
     * rendering surface.
     *
     * @param color Clear color in RGB format.
     */
    auto SetClearColor(const Color& color) -> void;

    /**
     * @brief Returns the number of renderable objects drawn in the last frame.
     *
     * Intended for statistics overlays and debugging.
     */
    [[nodiscard]] auto RenderedObjectsPerFrame() const -> size_t;

    virtual ~Renderer();

private:
    /// @cond INTERNAL
    class Impl;
    std::unique_ptr<Impl> impl_;
    /// @endcond
};

}