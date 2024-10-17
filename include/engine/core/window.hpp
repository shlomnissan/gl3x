// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <functional>
#include <memory>
#include <string>
#include <string_view>

namespace engine {

/**
 * @brief General interface for creating and managing a window.
 */
class ENGINE_EXPORT Window {
public:
    /**
     * @brief Parameters used to initialize the window.
     */
    struct Parameters {
        int width = 800;        ///< Width of the window in pixels.
        int height = 600;       ///< Height of the window in pixels.
        std::string_view title; ///< Title of the window.
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
    auto Start(const std::function<void(const double)>& tick) const -> void;

    auto HasErrors() const -> bool;

private:
    /// @brief Forward declaration of the implementation class.
    class Impl;

    /// @brief Pointer to the implementation class.
    std::unique_ptr<Impl> impl_ {nullptr};
};

}