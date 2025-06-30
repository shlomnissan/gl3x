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
 * @brief Entry point for defining and launching a Gleam application.
 *
 * The `ApplicationContext` class provides the main lifecycle hooks for setting
 * up a Gleam-based application. Users subclass this context and override key
 * methods such as `Configure`, `CreateScene`, and `Update` to define rendering
 * behavior, application parameters, and frame updates.
 *
 * Typical usage involves creating a subclass and overriding the relevant
 * virtual methods:
 *
 * @code
 * class MyApp : public gleam::ApplicationContext {
 * public:
 *   void Configure() override {
 *     params.title = "My App";
 *     params.width = 1280;
 *     params.height = 720;
 *     params.clear_color = 0x444444;
 *   }
 *
 *   std::shared_ptr<gleam::Scene> CreateScene() override {
 *     auto scene = gleam::Scene::Create();
 *     // Add nodes to the scene
 *     return scene;
 *   }
 *
 *     bool Update(float delta) override {
 *       // Called every frame
 *       return true;
 *     }
 * };
 *
 * int main() {
 *   MyApp app;
 *   app.Start();
 *   return 0;
 * }
 * @endcode
 *
 * The lifecycle of the application is managed entirely by calling `Start()`.
 * This internally sets up the rendering context, main loop, and invokes
 * user-defined behavior as appropriate.
 *
 * @ingroup CoreGroup
 */
class GLEAM_EXPORT ApplicationContext {
public:
    /**
     * @brief Configuration parameters for the application context.
     *
     * These values control window properties, rendering options, and debug settings.
     * Modify them by overriding the `Configure()` method in your subclass.
     */
    struct Parameters {
        std::string title {"Gleam Application"}; ///< Window title.
        Color clear_color {0x000000}; ///< Background clear color.
        int width {1024}; ///< Window width in pixels.
        int height {768}; ///< Window height in pixels.
        int antialiasing {0}; ///< Antialiasing level (e.g., 4x MSAA).
        bool vsync {true}; ///< Enables vertical sync.
        bool debug {false}; ///< Enables debug mode UI overlays.

        /**
         * @brief Returns the aspect ratio (width / height).
         *
         * @return float
         */
        [[nodiscard]] auto Ratio() const -> float {
            return static_cast<float>(width) / static_cast<float>(height);
        }
    };

    /**
     * @brief Constructs an ApplicationContext instance.
     *
     * Initializes internal state but does not start the application loop.
     */
    ApplicationContext();

    /**
     * @brief Starts the application loop.
     *
     * This method initializes the window, rendering context, and user scene
     * and enters the main loop until the application exits.
     */
    auto Start() -> void;

    /**
     * @brief Optional user configuration step.
     *
     * Override to customize the application parameters before startup.
     */
    virtual auto Configure() -> void {};

    /**
     * @brief Creates the root scene graph.
     *
     * This method **must be implemented** by the user and returns the primary
     * scene used for rendering and updates.
     *
     * @return std::shared_ptr<Scene>
     */
    virtual auto CreateScene() -> std::shared_ptr<Scene> = 0;

    /**
     * @brief Creates the main camera.
     *
     * This method can be optionally overridden. If null is returned, a default
     * 3D perspective camera will be created automatically.
     *
     * @return std::shared_ptr<Camera>
     */
    virtual auto CreateCamera() -> std::shared_ptr<Camera> { return nullptr; }

    /**
     * @brief Per-frame update callback.
     *
     * This method **must be implemented** and is called every frame with the
     * elapsed time since the last frame. Return `false` to exit the main loop.
     *
     * @param delta Time in seconds since the last frame.
     * @return `true` to continue running, `false` to exit the main loop.
     */
    virtual auto Update(float delta) -> bool = 0;

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
    virtual ~ApplicationContext();

protected:
    /// @brief Application configuration parameters.
    Parameters params;

    /// @brief Internal timer used to calculate frame delta.
    Timer timer {false};

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

    auto Setup() -> void;

    auto CreateDefaultCamera() const -> std::shared_ptr<Camera>;
};

}