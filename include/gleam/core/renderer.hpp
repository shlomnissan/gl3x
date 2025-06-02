/*
===========================================================================
GLEAM ENGINE https://gleamengine.org
Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/nodes/camera.hpp"
#include "gleam/math/color.hpp"
#include "gleam/nodes/scene.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Handles rendering of a scene using a specific camera.
 */
class GLEAM_EXPORT Renderer {
public:
    /**
     * @brief Parameters used to initialize the renderer.
     */
    struct Parameters {
        int width;  ///< The width of the rendering viewport.
        int height; ///< The height of the rendering viewport.
    };

    /**
     * @brief Constructs a Renderer object.
     *
     * @param params The parameters used to configure the renderer.
     */
    explicit Renderer(const Renderer::Parameters& params);

    /**
     * @brief Renders a scene from the perspective of the given camera.
     *
     * @param scene A pointer to the scene to be rendered.
     * @param camera A pointer to the camera defining the viewpoint for rendering.
     */
    auto Render(Scene* scene, Camera* camera) -> void;

    /**
     * @brief Sets the color to clear the screen with.
     *
     * @param color The color to clear the screen with.
     */
    auto SetClearColor(const Color& color) -> void;

    /**
     * @brief Gets the number of objects rendered per frame.
     *
     * @return size_t The number of objects rendered per frame.
     */
    [[nodiscard]] auto RenderedObjectsPerFrame() const -> size_t;

    /**
     * @brief Destructor for the Renderer class.
     */
    ~Renderer();

private:
    // Forward declarations
    class Impl;

    /// @brief Unique pointer to the Renderer implementation.
    std::unique_ptr<Impl> impl_;
};

}