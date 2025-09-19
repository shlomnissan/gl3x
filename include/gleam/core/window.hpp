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
     * @brief Processes pending window and input events.
     *
     * Polls the operating system for events such as input, window resize,
     * or close requests. Must be called regularly to keep the window responsive.
     */
    auto PollEvents() -> void;

    /**
     * @brief Marks the beginning of a new UI frame.
     *
     * Call this once per frame before issuing any UI commands.
     *
     * @note If no UI system is active, this is a no-op.
     */
    auto BeginUIFrame() -> void;

    /**
     * @brief Marks the end of the current UI frame.
     *
     * Call this once per frame after all UI commands have been issued.
     *
     * @note If no UI system is active, this is a no-op.
     */
    auto EndUIFrame() -> void;

    /**
     * @brief Swaps the front and back buffers.
     *
     * Presents the rendered frame to the display. Should be called once per
     * frame after rendering and UI submission.
     */
    auto SwapBuffers() -> void;

    /**
     * @brief Requests that the window be closed.
     *
     * Sets the internal close flag so that `ShouldClose()` returns true.
     * This allows the application to exit the main loop gracefully.
     */
    auto RequestClose() -> void;

    /**
     * @brief Returns whether the window has been flagged for closing.
     *
     * This flag is set when the user requests the window to close through
     * the operating system or when `RequestClose()` is called.
     *
     * @return `true` if the window should close, `false` otherwise.
     */
    auto ShouldClose() -> bool;

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
     * @brief Updates the window title string.
     *
     * @param title UTF-8 string to display in the window title bar.
     */
    auto SetTitle(std::string_view title) -> void;

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