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
 *     void Configure() override {
 *         params.title = "My App";
 *         params.width = 1280;
 *         params.height = 720;
 *         params.clear_color = 0x444444;
 *     }
 *
 *     std::shared_ptr<gleam::Scene> CreateScene() override {
 *         auto scene = gleam::Scene::Create();
 *         // Add nodes to the scene
 *         return scene;
 *     }
 *
 *     bool Update(float delta) override {
 *         // Called every frame
 *         return true;
 *     }
 * };
 *
 * int main() {
 *     MyApp app;
 *     app.Start();
 *     return 0;
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

    ApplicationContext();

    auto Start() -> void;

    virtual auto Configure() -> void {};

    virtual auto CreateScene() -> std::shared_ptr<Scene> = 0;

    virtual auto CreateCamera() -> std::shared_ptr<Camera> { return nullptr; }

    virtual auto Update(float delta) -> bool = 0;

    [[nodiscard]] auto GetScene() const -> Scene*;

    [[nodiscard]] auto GetCamera() const -> Camera*;

    auto SetScene(std::shared_ptr<Scene> scene) -> void;

    auto SetCamera(std::shared_ptr<Camera> camera) -> void;

    virtual ~ApplicationContext();

protected:
    Parameters params;

    Timer timer {false};

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

    auto Setup() -> void;

    auto CreateDefaultCamera() const -> std::shared_ptr<Camera>;
};

}