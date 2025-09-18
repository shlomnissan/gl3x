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

class Window;
class Camera;

/**
 * @brief Provides access to shared parameters and services.
 *
 * The `SharedContext` class encapsulates common runtime parameters and
 * services that are shared across the scene graph. This context is created
 * internally within the runtime and made available to nodes once they are
 * added to the active scene.
 *
 * Access to the shared context is provided through the
 * `Node::OnAttached(SharedContextPointer context)` callback, which is invoked
 * when the node becomes part of an active scene hierarchy. Override this
 * method in your node class to perform initialization that depends on the
 * context, such as loading resources, accessing the active camera, etc.
 *
 * @code
 * class MyNode : public gleam::Node {
 * public:
 *   void OnAttached(SharedContextPointer context) override {
 *     context->Loaders().Texture->LoadAsync(
 *       "assets/checker.tex",
 *       [this](auto result) {
 *         if (result) {
 *           texture_ = result.value();
 *         } else {
 *           std::println(stderr, "{}", result.error());
 *         }
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
    friend class Application;

    /**
     * @brief Runtime parameters shared across systems.
     */
    struct SharedParameters {
        Camera* camera; ///< Current active camera.
        float aspect_ratio; ///< Aspect ratio of the render surface.
        int framebuffer_width; ///< Framebuffer width in physical pixels.
        int framebuffer_height; ///< Frambuffer height in physical pixels.
        int window_width; ///< Window width in logical units.
        int window_height; ///< Window height in logical units.
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

    // Non-copyable
    SharedContext(const SharedContext&) = delete;
    auto operator=(const SharedContext&) -> SharedContext& = delete;

    // Movable
    SharedContext(SharedContext&&) noexcept = default;
    auto operator=(SharedContext&&) noexcept -> SharedContext& = default;

    /**
     * @brief Creates a unique pointer to a shared context object.
     *
     * @param window Pointer to an initialized window instance.
     * @param camera Pointer to the active camera instance.
     *
     * @note This function is normally invoked by the runtime. It is exposed
     * publicly to allow explicit initialization when needed.
     *
     * Each application should maintain only a single instance of
     * `SharedContext`. If you initialize it directly, you are responsible
     * for keeping the active camera reference in sync with the context.
     */
    static auto Create(Window* window, Camera* camera) -> std::unique_ptr<SharedContext>;

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

using SharedContextPointer = const gleam::SharedContext*;