// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "gleam_export.h"

#include "gleam/core/renderer.hpp"
#include "gleam/core/shared_context.hpp"
#include "gleam/core/timer.hpp"
#include "gleam/core/window.hpp"
#include "gleam/nodes/camera.hpp"
#include "gleam/nodes/scene.hpp"

#include <memory>

namespace gleam {

class PerformanceGraph;

/**
 * @brief Base class responsible for setting up a common context for applications.
 */
class GLEAM_EXPORT ApplicationContext {
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
     * @brief Retrieves the shared context of the application.
     *
     * @return A raw pointer to the shared context.
     */
    [[nodiscard]] auto Context() const -> const SharedContext*;

    /**
     * @brief Destructor for the application context.
     */
    virtual ~ApplicationContext();

private:
    /// @brief Performance graph used to display performance metrics.
    std::unique_ptr<PerformanceGraph> performance_graph_;

    /// @brief The scene managed by the application context.
    std::shared_ptr<Scene> scene_ {nullptr};

    /// @brief The camera managed by the application context.
    std::shared_ptr<Camera> camera_ {nullptr};

    /// @brief The window managed by the application context.
    std::unique_ptr<Window> window_ {nullptr};

    /// @brief The renderer managed by the application context.
    std::unique_ptr<Renderer> renderer_ {nullptr};

    /// @brief The shared context propgated through the scene graph.
    std::unique_ptr<SharedContext> shared_context_ {nullptr};

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