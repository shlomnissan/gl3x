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
    * @brief Constructs a Window with the given title, width, and height.
    * 
    * This constructor initializes a window with the specified title, width, and height. 
    * If width and height are not provided, they default to 800 and 600 pixels respectively.
    * 
    * @param title The title of the window.
    * @param width The width of the window in pixels. Defaults to 800.
    * @param height The height of the window in pixels. Defaults to 600.
    */
    Window(std::string_view title, int width = 800, int height = 600);

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
    [[nodiscard]] auto width() const -> int;

    /**
     * @brief Gets the height of the window.
     * 
     * @return The height of the window in pixels.
     */
    [[nodiscard]] auto height() const -> int;
    
    /**
    * @brief Starts the main loop of the window.
    * 
    * @param tick A callback function that will be invoked each frame
    * with the time elapsed since the last frame (delta time). The function
    * takes a single `double` argument representing the elapsed time in seconds.
    */
    auto Start(const std::function<void(const double)>& tick) const -> void;

private:
    /// @brief Forward declaration of the implementation class.
    class Impl;

    /// @brief Pointer to the implementation class.
    std::unique_ptr<Impl> impl_ {nullptr};
};

}