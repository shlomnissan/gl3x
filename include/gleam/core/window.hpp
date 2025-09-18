/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include <expected>
#include <functional>
#include <memory>
#include <string>
#include <string_view>

namespace gleam {

class Event;

// TODO: delete: Window shouldn't own the main loop
using OnTickCallback = std::function<void()>;

/**
 * @brief Cross-platform application window.
 *
 * The `Window` class creates the OS window and manages the framebuffer.
 * It is typically managed by the `Application` runtime, but can also be
 * constructed directly for manual initialization flows.
 *
 * Typical usage:
 * @code
 * gleam::Window window({
 *   .title = "My App",
 *   .width = 1280,
 *   .height = 720,
 *   .antialiasing = 4,
 *   .vsync = true
 * });
 *
 * auto ok = window.Initialize();
 * if (!ok) {
 *   HandleError(ok.error());
 * }
 * @endcode
 *
 * @note Preferred usage is through the `Application` runtime, which wires the
 * window, renderer, and scene automatically. Use direct initialization when you
 * need full control over the main loop.
 *
 * @ingroup CoreGroup
 */
class GLEAM_EXPORT Window {
public:
    /// @cond INTERNAL
    class Impl;
    /// @endcond

    /// @brief Construction parameters for `Window`.
    struct Parameters {
        std::string title; ///< Window title string.
        int width; ///< Client-area width in pixels.
        int height; ///< Client-area height in pixels.
        int antialiasing; ///< Multisample anti-aliasing sample count.
        bool vsync; ///< Enable or disable vertical sync.
    };

    /**
     * @brief Constructs a window object with the given parameters.
     *
     * The window resources are not created until `Initialize()` is called.
     *
     * @param params Window::Parameters
     */
    explicit Window(const Window::Parameters& params);

    // Non-copyable
    Window(const Window&) = delete;
    auto operator=(const Window&) -> Window& = delete;

    // Movable
    Window(Window&&) noexcept = default;
    auto operator=(Window&&) noexcept -> Window& = default;

    /**
     * @brief Initializes the underlying OS window and graphics context.
     *
     * @return `std::expected<void, std::string>` empty on success, or an
     * error message on failure.
     */
    [[nodiscard]] auto Initialize() -> std::expected<void, std::string>;

    /**
     * @brief Returns the current framebuffer width in pixels.
     *
     * On HiDPI displays this may differ from `Width()`.
     */
    [[nodiscard]] auto FramebufferWidth() const -> int;

    /**
     * @brief Returns the current framebuffer height in pixels.
     *
     * On HiDPI displays this may differ from `Height()`.
     */
    [[nodiscard]] auto FramebufferHeight() const -> int;

    /**
     * @brief Returns the current logical window width in pixels.
     */
    [[nodiscard]] auto Width() const -> int;

    /**
     * @brief Returns the current logical window height in pixels.
     */
    [[nodiscard]] auto Height() const -> int;

    /**
     * @brief Returns the logical aspect ratio (width / height).
     */
    [[nodiscard]] auto AspectRatio() const -> float;

    /**
     * @brief Enters the main loop and invokes `tick` once per frame.
     *
     * @param tick User-provided per-frame callback.
     */
    auto Start(const OnTickCallback& tick) const -> void;

    /**
     * @brief Requests to break out of the main loop.
     *
     * The loop will exit after the current frame finishes.
     */
    auto Break() -> void;

    /**
     * @brief Releases window resources.
     */
    ~Window() noexcept;

private:
    /// @cond INTERNAL
    std::unique_ptr<Impl> impl_;
    /// @endcond
};

}