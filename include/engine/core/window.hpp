// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

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

private:
    /// @brief Forward declaration of the implementation class.
    class Impl;

    /// @brief Pointer to the implementation class.
    std::unique_ptr<Impl> impl_;
};

}