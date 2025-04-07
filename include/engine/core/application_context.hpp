// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"

#include "engine/core/renderer.hpp"
#include "engine/core/timer.hpp"
#include "engine/core/window.hpp"
#include "engine/nodes/camera.hpp"
#include "engine/nodes/scene.hpp"

#include <memory>

namespace engine {

class PerformanceGraph;

/**
 * @brief Base class responsible for setting up a common context for applications.
 */
class ENGINE_EXPORT ApplicationContext {
public:
    /**
     * @brief Parameters for configuring the application context.
     */
    struct Parameters {
        int width {1024};     ///< Width of the window in pixels.
        int height {768};     ///< Height of the window in pixels.
        int antialiasing {4}; ///< Number of samples for multisampling.
        bool vsync {true};    ///< Enable vertical synchronization.
        bool debug {false};   ///< Render the performance graph.
    };

    /**
     * @brief Default parameters for the application context.
     */
    Parameters params;

    /// @brief The timer used to measure elapsed time.
    Timer timer {false};

    /**
     * @brief Default constructor.
     */
    ApplicationContext();

    /**
     * @brief Sets up the application context.
     *
     * This method can be overridden by the client to provide custom setup logic.
     * If the client overrides this method, they must call the base class Setup function first.
     */
    virtual auto Setup() -> void;

    /**
     * @brief Configures the application context.
     */
    virtual auto Configure() -> void = 0;

    /**
     * @brief Updates the application context.
     *
     * @param delta The time in seconds since the last update.
     * @return A boolean indicating whether the application should break the game loop.
     */
    virtual auto Update(float delta) -> bool = 0;

    /**
     * @brief Starts the application context.
     *
     * This method starts the main loop of the application.
     */
    auto Start() -> void;

    /**
     * @brief Sets the scene for the application context.
     *
     * @param scene A shared pointer to the scene to be set.
     */
    auto SetScene(std::shared_ptr<Scene> scene) -> void;

    /**
     * @brief Sets the camera for the application context.
     *
     * @param camera A shared pointer to the camera to be set.
     */
    auto SetCamera(std::shared_ptr<Camera> camera) -> void;

    /**
     * @brief Sets the title of the application window.
     *
     * @param title The title to be set for the window.
     */
    auto SetTitle(std::string_view title) -> void;

    /**
     * @brief Sets the clear color for the renderer.
     *
     * @param color The color to be set as the clear color.
     */
    auto SetClearColor(const Color& color) -> void;

    /**
     * @brief Gets the aspect ratio of the application window.
     *
     * @return The aspect ratio of the application window.
     */
    [[nodiscard]] auto AspectRatio() const {
        return window_->AspectRatio();
    }

    /**
     * @brief Destructor for the application context.
     */
    virtual ~ApplicationContext();

private:
    /// @brief Performance graph used to display performance metrics.
    std::unique_ptr<PerformanceGraph> performance_graph_ {nullptr};

    /// @brief The scene managed by the application context.
    std::shared_ptr<Scene> scene_ {nullptr};

    /// @brief The camera managed by the application context.
    std::shared_ptr<Camera> camera_ {nullptr};

    /// @brief The window managed by the application context.
    std::unique_ptr<Window> window_ {nullptr};

    /// @brief The renderer managed by the application context.
    std::unique_ptr<Renderer> renderer_ {nullptr};

    /// @brief Indicates whether the application context has been initialized.
    bool initialized_ {false};

    /**
     * @brief Initializes the window.
     */
    auto InitializeWindow() -> bool;

    /**
     * @brief Initializes the renderer.
     */
    auto InitializeRenderer() -> bool;
};

}