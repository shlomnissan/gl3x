// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"

#include <memory>
#include <vector>

namespace engine {

/**
 * @brief Base class for nodes in a scene graph.
 */
class ENGINE_EXPORT Node {
public:
    /**
     * @brief Creates a new shared pointer to a Node.
     *
     * @return A shared pointer to a newly created `Node` instance.
     */
    static auto Create() {
        return std::make_shared<Node>();
    }

    /**
     * @brief Adds a child node to this node.
     *
     * @param node A shared pointer to the node to be added as a child.
     */
    auto Add(const std::shared_ptr<Node>& node) -> void;

    /**
     * @brief Removes a child node from this node.
     *
     * @param node A shared pointer to the node to be removed from the children list.
     */
    auto Remove(const std::shared_ptr<Node>& node) -> void;

    /**
     * @brief Retrieves the list of child nodes.
     *
     * @return A constant reference to a vector of shared pointers to child nodes.
     */
    auto Children() const -> const std::vector<std::shared_ptr<Node>>&;

    /**
     * @brief Retrieves the parent node.
     *
     * @return A constant pointer to the parent node, or `nullptr` if this node has no parent.
     */
    auto Parent() const -> const Node* {
        return parent_;
    }

private:
    /// @brief Pointer to the parent node.
    Node* parent_ {nullptr};

    /// @brief List of child nodes.
    std::vector<std::shared_ptr<Node>> children_;
};

}