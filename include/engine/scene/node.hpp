// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"
#include "engine/math/transform3d.hpp"

#include <memory>
#include <vector>

namespace engine {

/**
 * @brief Represents a node in a scene graph.
 */
class ENGINE_EXPORT Node {
public:
    /**
     * @brief Adds a child node to this node.
     *
     * @param node A shared pointer to the node to add.
     */
    auto Add(const std::shared_ptr<Node>& node) -> void;

    /**
     * @brief Removes a child node from this node.
     *
     * @param node A shared pointer to the node to remove.
     */
    auto Remove(const std::shared_ptr<Node>& node) -> void;

    /**
     * @brief Retrieves the list of child nodes.
     *
     * @return A constant reference to a vector of child nodes.
     */
    [[nodiscard]]
    auto Children() const -> const std::vector<std::shared_ptr<Node>>&;

    /**
     * @brief Checks if the node's children should be updated.
     *
     * @return True if children need updating, false otherwise.
     */
    [[nodiscard]]
    auto ShouldUpdateChildren() const -> bool;

    /**
     * @brief Updates the node's world transform and propagates updates to children.
     */
    auto UpdateTransforms() -> void;

    /**
     * @brief Retrieves the world transform matrix of the node.
     *
     * @return The world transform matrix.
     */
    [[nodiscard]]
    auto GetWorldTransform() const -> Matrix4;

    /**
     * @brief Scales the node's local transformation.
     *
     * @param value The scaling factor.
     */
    auto Scale(float value) -> void;

    /**
     * @brief Rotates the node around the X axis.
     *
     * @param angle The angle to rotate around the X axis, in radians.
     */
    auto RotateX(float angle) -> void;

    /**
     * @brief Rotates the node around the Y axis.
     *
     * @param angle The angle to rotate around the Y axis, in radians.
     */
    auto RotateY(float angle) -> void;

    /**
     * @brief Rotates the node around the Z axis.
     *
     * @param angle The angle to rotate around the Z axis, in radians.
     */
    auto RotateZ(float angle) -> void;

    /**
     * @brief Translates the node along the X axis.
     *
     * @param distance The translation distance.
     */
    auto TranslateX(float distance) -> void;

    /**
     * @brief Translates the node along the Y axis.
     *
     * @param distance The translation distance.
     */
    auto TranslateY(float distance) -> void;

    /**
     * @brief Translates the node along the Z axis.
     *
     * @param distance The translation distance.
     */
    auto TranslateZ(float distance) -> void;

private:
    /// @brief Flag indicating if children need updating.
    bool update_children_ {false};

    /// @brief Pointer to the parent node.
    Node* parent_ {nullptr};

    /// @brief List of child nodes.
    std::vector<std::shared_ptr<Node>> children_;

    /// @brief Node's local transformation.
    Transform3D local_transform_;

    /// @brief Node's world transform matrix.
    Matrix4 world_transform_ {1.0f};

    /**
     * @brief Determines if the node's transform should be updated.
     *
     * @return True if the transform is dirty or the parent requires an update.
     */
    [[nodiscard]]
    auto ShouldUpdateTransform() const -> bool;
};

}