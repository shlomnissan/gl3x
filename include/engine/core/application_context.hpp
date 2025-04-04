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
        int width {1024};      ///< Width of the window in pixels.
        int height {768};      ///< Height of the window in pixels.
        int antialiasing {4};  ///< Number of samples for multisampling.
        bool vsync {true};     ///< Enable vertical synchronization.
        bool debug {false};    ///< Render application debug window.
    };

    /**
     * @brief Default parameters for the application context.
     */
    Parameters params;

    /// @brief The window managed by the application context.
    std::unique_ptr<Window> window {nullptr};

    /// @brief The renderer managed by the application context.
    std::unique_ptr<Renderer> renderer {nullptr};

    /// @brief The scene managed by the application context.
    std::shared_ptr<Scene> scene {nullptr};

    /// @brief The camera managed by the application context.
    std::shared_ptr<Camera> camera {nullptr};

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

    /**
     * @brief Destructor for the application context.
     */
    virtual ~ApplicationContext();

private:
    /// @brief Performance graph used to display performance metrics.
    std::unique_ptr<PerformanceGraph> performance_graph_ {nullptr};

    /// @brief The time structure used to measure the frame rate.
    struct Time {
        double last_frame_time = 0.0;
        double last_frame_rate_update = 0.0;
        double frame_time = 0.0;
        unsigned int frame_count = 0;
    };

    /// @brief The time structure used to measure the frame rate.
    Time time_;

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