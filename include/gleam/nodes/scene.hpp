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

class GLEAM_EXPORT Scene : public Node {
public:
    std::unique_ptr<Fog> fog;

    /**
     * @brief Constructs an Scene instance.
     */
    Scene();

    auto ProcessUpdates(float delta) -> void;

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
    /// @endcond
};

}