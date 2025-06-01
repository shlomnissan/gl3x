// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include <functional>
#include <memory>
#include <string>
#include <string_view>

namespace gleam {

class Event;

using OnTickCallback = std::function<void()>;
using OnEventCallback = std::function<void(std::unique_ptr<Event> event)>;

/**
 * @brief General interface for creating and managing a window.
 */
class GLEAM_EXPORT Window {
public:
    /**
     * @brief Parameters used to initialize the window.
     */
    struct Parameters {
        int width;          ///< Width of the window in pixels.
        int height;         ///< Height of the window in pixels.
        int antialiasing;   ///< Number of samples for multisampling.
        bool vsync;         ///< Enable vertical synchronization.
    };

    /**
     * @brief Constructs a Window object with the given parameters.
     *
     * @param params The parameters used to create the window.
     */
    explicit Window(const Window::Parameters& params);

    /**
     * @brief Destroys the Window object.
     *
     * @note The destructor is defined in the source file to handle the complete type `Impl`.
     */
    ~Window();

    /**
     * @brief Gets the width of the window.
     *
     * @return The width of the window in pixels.
     */
    [[nodiscard]] auto Width() const -> int;

    /**
     * @brief Gets the height of the window.
     *
     * @return The height of the window in pixels.
     */
    [[nodiscard]] auto Height() const -> int;

    /**
     * @brief Gets the aspect ratio of the window.
     *
     * @return The aspect ratio of the window in pixels.
     */
    [[nodiscard]] auto AspectRatio() const -> float;

    /**
    * @brief Starts the main loop of the window.
    *
    * @param tick A callback function that will be invoked each frame
    * with the time elapsed since the last frame (delta time). The function
    * takes a single `double` argument representing the elapsed time in seconds.
    */
    auto Start(const OnTickCallback& tick) const -> void;

    /**
     * @brief If this method is called while the loop is running, it will stop the loop.
     */
    auto Break() -> void;

    /**
     * @brief Sets the title of the window.
     *
     * @param title The new title of the window.
     */
    auto SetTitle(std::string_view title) -> void;

    /**
     * @brief Checks if there are any errors associated with the window.
     *
     * @return `true` if errors exist, `false` otherwise.
     */
    auto HasErrors() const -> bool;

    /// Forward declarations
    class Impl;

private:
    /// @brief Pointer to the implementation class.
    std::unique_ptr<Impl> impl_;
};

}