/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/cameras/camera.hpp"
#include "gleam/core/timer.hpp"
#include "gleam/math/color.hpp"
#include "gleam/nodes/scene.hpp"

#include <memory>
#include <string>

namespace gleam {

/**
 * @brief The runtime entry point for defining and launching an app.
 *
 * The `Application` class is the runtime: it sets up the window,
 * rendering context, a main loop, and calls your hooks. Subclass it and
 * override `Configure`, `CreateScene`, and `Update` to define behavior.
 *
 * This is the preferred way to initialize a new app. If you need
 * complete control, you can also assemble a program manually (window,
 * renderer, loop, etc.), but that is outside the scope of this runtime API.
 *
 * Typical usage:
 *
 * @code
 * class MyApp : public gleam::Application {
 *  public:
 *   auto Configure() -> Application::Parameters override {
 *     return {
 *       .title = "My App",
 *       .width = 1024,
 *       .height = 768,
 *       .clear_color = 0x444444,
 *       .vsync = true,
 *       .show_stats = true
 *     };
 *   }
 *
 *   auto CreateScene() -> std::shared_ptr<gleam::Scene> override {
 *     auto scene = gleam::Scene::Create();
 *     // Add nodes to the scene...
 *     return scene;
 *   }
 *
 *   // Optional: override CreateCamera() to provide your own camera.
 *   // Returning nullptr creates a default perspective camera.
 *   // auto CreateCamera() -> std::shared_ptr<gleam::Camera> override { ... }
 *
 *   auto Update(float delta) -> bool override {
 *     // Per-frame logic. Return false to exit the main loop.
 *     return true;
 *   }
 * };
 *
 * int main() {
 *   MyApp app;
 *   app.Start();
 *   return 0;
 * }
 * @endcode
 *
 * Calling `Start()` initializes the runtime, constructs the user scene (and
 * camera, if provided), then runs the main loop while invoking `Update()`
 * each frame.
 *
 * @ingroup CoreGroup
 */
class GLEAM_EXPORT Application {
public:
    /**
     * @brief Configuration parameters for the application context.
     */
    struct Parameters {
        std::string title {"Application"}; ///< Window title.
        Color clear_color {0x000000}; ///< Background clear color.
        int width {1024}; ///< Window width in pixels.
        int height {768}; ///< Window height in pixels.
        int antialiasing {0}; ///< Antialiasing level (e.g., 4x MSAA).
        bool vsync {true}; ///< Enables vertical sync.
        bool show_stats {false}; ///< Show stats UI overlay.
    };

    /**
     * @brief Constructs an Application instance.
     *
     * Initializes internal state but does not start the application loop.
     */
    Application();

    /**
     * @brief Starts the application loop.
     *
     * This method initializes the window, rendering context, and user scene
     * and enters the main loop until the application exits.
     */
    auto Start() -> void;

    /**
     * @brief Provides configuration parameters for the application.
     *
     * Override this method to customize window settings, clear color,
     * antialiasing, vsync, and other runtime options before the
     * application starts.
     *
     * @return Parameters struct containing application configuration.
     */
    virtual auto Configure() -> Parameters {
        return Parameters {};
    };

    /**
     * @brief Creates the root scene graph.
     *
     * This method must be implemented by the user and returns the primary
     * scene used for rendering and updates.
     *
     * @return std::shared_ptr<Scene>
     */
    virtual auto CreateScene() -> std::shared_ptr<Scene> = 0;

    /**
     * @brief Creates the main camera.
     *
     * This method can be optionally overridden. If null is returned, a default
     * perspective camera will be created automatically.
     *
     * @return std::shared_ptr<Camera>
     */
    virtual auto CreateCamera() -> std::shared_ptr<Camera> { return nullptr; }

    /**
     * @brief Per-frame update callback.
     *
     * This method must be implemented and is called every frame with the
     * elapsed time since the last frame. Return `false` to exit the main loop.
     *
     * @param delta Time in seconds since the last frame.
     * @return `true` to continue running, `false` to exit the main loop.
     */
    virtual auto Update(float delta) -> bool = 0;

    /**
     * @brief Returns the runtime parameters shared across subsystems.
     *
     * These values are populated once the application is initialized and
     * reflect the current state of the runtime (e.g., active camera,
     * aspect ratio, framebuffer and window sizes).
     *
     * Useful for querying real window/framebuffer dimensions or the
     * current camera when setting up nodes at runtime.
     *
     * @return SharedContext::SharedParameters containing current runtime parameters.
     */
    [[nodiscard]] auto GetParameters() const -> SharedContext::SharedParameters;

    /**
     * @brief Returns the current scene pointer.
     *
     * @return Scene*
     */
    [[nodiscard]] auto GetScene() const -> Scene*;

    /**
     * @brief Returns the current camera pointer.
     *
     * @return Camera*
     */
    [[nodiscard]] auto GetCamera() const -> Camera*;

    /**
     * @brief Sets the active scene.
     *
     * @param scene Shared pointer to the new scene.
     */
    auto SetScene(std::shared_ptr<Scene> scene) -> void;

    /**
     * @brief Sets the active camera.
     *
     * @param camera Shared pointer to the new camera.
     */
    auto SetCamera(std::shared_ptr<Camera> camera) -> void;

    /**
     * @brief Destructor.
     */
    virtual ~Application();

private:
    /// @cond INTERNAL
    class Impl;
    std::unique_ptr<Impl> impl_;

    Timer timer_ {false};

    bool show_stats_ = false;

    auto Setup() -> void;
    /// @endcond
};

}