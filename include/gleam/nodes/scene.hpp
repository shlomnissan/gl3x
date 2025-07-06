/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"

#include "gleam/nodes/fog.hpp"
#include "gleam/nodes/node.hpp"

#include <memory>

namespace gleam {

/**
 * @brief Root node and entry point for a scene graph.
 *
 * `Scene` is the top-level container for all nodes in a Gleam application. It acts as the
 * root of the scene graph and is responsible for propagating update and input events
 * throughout the hierarchy. Each application has one active scene at a time, which is
 * managed by the `ApplicationContext`.
 *
 * A custom scene can be created by inheriting from this class and overriding behavior
 * or adding initial nodes. The scene must be provided to the application during startup:
 *
 * @code
 * class MyApp : public gleam::ApplicationContext {
 * public:
 *   auto Configure() -> void override {
 *     params.title = "My App";
 *   }
 *
 *   auto CreateScene() -> std::shared_ptr<gleam::Scene> override {
 *     auto scene = gleam::Scene::Create();
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
 * Attaching a new scene using gleam::ApplicationContext::SetScene replaces the current one.
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT Scene : public Node {
public:
    /**
     * @brief Fog settings applied to the entire scene.
     *
     * Set this to a `LinearFog` or `ExponentialFog` instance to enable distance-based
     * atmospheric fading. This is typically done during scene setup.
     *
     * @code
     * scene->fog = gleam::LinearFog::Create(0x444444, 2.0f, 6.0f);
     * @endcode
     *
     * @see gleam::LinearFog
     * @see gleam::ExponentialFog
     */
    std::unique_ptr<Fog> fog;

    /**
     * @brief Constructs an Scene instance.
     */
    Scene();

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

    friend class Renderer;
    bool touched_ = false;

    friend class ApplicationContext;
    auto SetContext(SharedContext* context) -> void;
    auto ProcessUpdates(float delta) -> void;
    /// @endcond
};

}