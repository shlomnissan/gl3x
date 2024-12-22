// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/color.hpp"
#include "engine/nodes/scene.hpp"

#include "nodes/camera.hpp"

#include <memory>

namespace engine {

/**
 * @brief Handles rendering of a scene using a specific camera.
 */
class ENGINE_EXPORT Renderer {
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
     * @brief Destructor for the Renderer class.
     */
    ~Renderer();

private:
    /**
     * @brief Forward declaration of the implementation details.
     */
    class Impl;

    /// @brief Unique pointer to the Renderer implementation.
    std::unique_ptr<Impl> impl_ {nullptr};
};

}