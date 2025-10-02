/*
===========================================================================
  GL3X https://gl3x.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gl3x_export.h"

#include "gl3x/nodes/fog.hpp"
#include "gl3x/nodes/node.hpp"

#include <memory>

namespace gl3x {

/**
 * @brief Root node and entry point for a scene graph.
 *
 * `Scene` is the top-level container for all nodes in a Gleam application. It acts as the
 * root of the scene graph and is responsible for propagating update and input events
 * throughout the hierarchy. Each application has one active scene at a time, which is
 * managed by the `Application`.
 *
 * A custom scene can be created by inheriting from this class and overriding behavior
 * or adding initial nodes. The scene must be provided to the application during startup:
 *
 * @code
 * class MyApp : public gl3x::Application {
 * public:
 *   auto Configure() -> void override {
 *     params.title = "My App";
 *   }
 *
 *   auto CreateScene() -> std::shared_ptr<gl3x::Scene> override {
 *     auto scene = gl3x::Scene::Create();
 *     // Add nodes to the scene
 *     return scene;
 *   }
 *
 *   auto Update(float delta) -> bool override {
 *     // Called every frame
 *     return true;
 *   }
 * };
 * @endcode
 *
 * @note Only one scene can be attached to the application context at a time.
 * Attaching a new scene using gl3x::Application::SetScene replaces the current one.
 *
 * @ingroup NodesGroup
 */
class GL3X_EXPORT Scene : public Node {
public:
    /**
     * @brief Fog settings applied to the entire scene.
     *
     * Set this to a `LinearFog` or `ExponentialFog` instance to enable distance-based
     * atmospheric fading. This is typically done during scene setup.
     *
     * @code
     * scene->fog = gl3x::LinearFog::Create(0x444444, 2.0f, 6.0f);
     * @endcode
     *
     * @see gl3x::LinearFog
     * @see gl3x::ExponentialFog
     */
    std::unique_ptr<Fog> fog;

    /**
     * @brief Constructs an Scene instance.
     */
    Scene();

    /**
     * @brief Advances the scene by one frame.
     *
     * Propagates the per-frame update through the scene graph, calling
     * `Node::Update(float delta)` on all attached nodes in depth-first order.
     * This is invoked automatically by the runtime each frame.
     *
     * @param delta Elapsed time in seconds since the last frame.
     */
    auto Advance(float delta) -> void;

    /**
     * @brief Attaches a shared context to the scene.
     * @deprecated
     *
     * The context provides runtime parameters (e.g., window size, active camera)
     * and resource loaders. This is normally called by the runtime during
     * initialization. All nodes added to the scene will receive the context
     * via `Node::OnAttached`.
     *
     * @param context Pointer to the active SharedContext instance (const).
     */
    auto SetContext(SharedContextPointer context) -> void;

    /**
     * @brief Creates a shared pointer to a Scene object.
     *
     * @return std::shared_ptr<Scene>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Scene>();
    }

    /**
     * @brief Returns node type.
     *
     * @return NodeType::SceneNode
     */
    [[nodiscard]] auto GetNodeType() const -> NodeType override {
        return NodeType::SceneNode;
    }

    /**
     * @brief Destructor.
     */
    ~Scene() override;

private:
    /// @cond INTERNAL
    class Impl;
    std::unique_ptr<Impl> impl_;
    /// @endcond
};

}