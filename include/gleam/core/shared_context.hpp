/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/loaders.hpp"

#include <memory>

namespace gleam {

class Camera;

/**
 * @brief Provides access to shared engine parameters and services.
 *
 * The `SharedContext` class encapsulates common runtime parameters and
 * services that are shared across the Gleam engine. This context is created
 * internally and made available to nodes and systems once they are attached
 * to the scene graph.
 *
 * Access to the shared context is provided through the `Node::OnAttached(gleam::SharedContext* context)` callback,
 * which is invoked when the node becomes part of an active scene hierarchy.
 * Override this method in your node class to perform initialization that depends on the context,
 * such as loading resources, accessing the active camera, etc.
 *
 * @code
 * class MyNode : public gleam::Node {
 * public:
 *   void OnAttached(gleam::SharedContext* context) override {
 *     context->Loaders().Texture->LoadAsync(
 *       "assets/checker.tex",
 *       [this](auto result) {
 *         if (result) texture_ = result.value();
 *       }
 *     );
 *   }
 * };
 * @endcode
 *
 * @ingroup CoreGroup
 */
class GLEAM_EXPORT SharedContext {
public:
    friend class ApplicationContext;

    /**
     * @brief Runtime parameters shared across systems.
     */
    struct SharedParameters {
        Camera* camera; ///< Current active camera.
        float ratio; ///< Aspect ratio of the render surface.
        int width; ///< Framebuffer width in pixels.
        int height; ///< Framebuffer height in pixels.
        bool debug; ///< Whether the engine is running in debug mode.
    };

    /**
     * @brief Built-in resource loaders.
     *
     * Provides access to engine-supported loaders for loading textures and meshes.
     */
    struct SharedLoaders {
        /// @brief Texture loader instance.
        std::shared_ptr<TextureLoader> Texture = TextureLoader::Create();
        /// @brief Mesh loader instance.
        std::shared_ptr<MeshLoader> Mesh = MeshLoader::Create();
    };

    /**
     * @brief Constructs a SharedContext object.
     *
     * @param params SharedContext::SharedParameters
     */
    explicit SharedContext(const SharedParameters& params) : params_(params) {};

    /**
     * @brief Returns the current runtime parameters.
     *
     * @return Reference to `SharedContext::SharedParameters`.
     */
    [[nodiscard]] const SharedParameters& Parameters() const {
        return params_;
    }

    /**
     * @brief Returns resource loaders.
     *
     * @return Reference to `SharedContext::SharedLoaders`.
     */
    [[nodiscard]] const SharedLoaders& Loaders() const {
        return loaders_;
    }

private:
    /// @brief Internal parameter state.
    SharedParameters params_ {};

    /// @brief Internal loader registry.
    SharedLoaders loaders_ {};
};

}