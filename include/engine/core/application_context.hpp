// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine/core/renderer.hpp"
#include "engine/core/window.hpp"
#include "engine/scene/camera.hpp"
#include "engine/scene/scene.hpp"

#include <memory>

namespace engine {

/**
 * @brief Base class responsible for setting up a common context for applications.
 */
class ApplicationContext {
public:
    /**
     * @brief Parameters for configuring the application context.
     */
    struct Parameters {
        int width;          ///< Width of the window in pixels.
        int height;         ///< Height of the window in pixels.
        int antialiasing;   ///< Number of samples for multisampling.
        bool vsync;         ///< Enable vertical synchronization.
    };

    /**
     * @brief Default parameters for the application context.
     */
    Parameters params {
        .width = 1024,
        .height = 768,
        .antialiasing = 4,
        .vsync = true
    };

    /// @brief The window managed by the application context.
    std::unique_ptr<Window> window {nullptr};

    /// @brief The renderer managed by the application context.
    std::unique_ptr<Renderer> renderer {nullptr};

    /// @brief The scene managed by the application context.
    std::shared_ptr<Scene> scene {nullptr};

    /// @brief The camera managed by the application context.
    std::shared_ptr<Camera> camera {nullptr};

    /**
     * @brief Sets up the application context.
     *
     * This method can be overridden by the client to provide custom setup logic.
     * If the client overrides this method, they must call the base class Setup function first.
     */
    virtual auto Setup() -> void {
        InitializeWindow();
        InitializeRenderer();
        initialized_ = true;
    }

    /**
     * @brief Configures the application context.
     *
     * This method is a no-op by default and should be overridden by the client
     * to provide custom configuration by modifying the default values of the `params` variable.
     */
    virtual auto Configure() -> void {}

    /**
     * @brief Updates the application context.
     *
     * This method is a no-op by default and should be overridden by the client
     * to provide custom update logic.
     *
     * @param delta The time in seconds since the last update.
     * @return A boolean indicating whether the application should break the game loop.
     */
    virtual auto Update(float delta) -> bool {
        // No-op. The client should override this function.
        return true;
    }

    /**
     * @brief Starts the application context.
     *
     * This method starts the main loop of the application.
     */
    auto Start() -> void;


    virtual ~ApplicationContext() = default;

private:
    /// @brief Indicates whether the application context has been initialized.
    bool initialized_ {false};

    /**
     * @brief Initializes the window.
     *
     * This method sets up the window with the specified parameters.
     */
    auto InitializeWindow() -> bool;

    /**
     * @brief Initializes the renderer.
     *
     * This method sets up the renderer with the specified parameters.
     */
    auto InitializeRenderer() -> bool;
};

}