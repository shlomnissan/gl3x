// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "engine_export.h"
#include "engine/math/matrix4.hpp"
#include "engine/math/transform.hpp"
#include "engine/math/utilities.hpp"

#include <memory>
#include <string>
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
     * @brief Retrieves the parent node of this node.
     *
     * @return A pointer to the parent node. If this node has no parent, the return value will be a null pointer.
     */
    [[nodiscard]]
    auto Parent() const -> const Node*;

    /**
     * @brief Retrieves the unique identifier for this node.
     *
     * @return The UUID of the node as a string.
     */
    [[nodiscard]]
    const auto& UUID() const { return uuid_; }

    /**
     * @brief Checks if the node's children should be updated.
     *
     * @return True if children need updating, false otherwise.
     */
    [[nodiscard]]
    auto ShouldUpdateChildren() const -> bool;

    /**
     * @brief Determines if the node's transform should be updated.
     *
     * @return True if the transform is dirty or the parent requires an update.
     */
    [[nodiscard]]
    auto ShouldUpdateTransform() const -> bool;

    /**
     * @brief Updates the node's world transform and propagates updates to children.
     */
    virtual auto UpdateTransforms() -> void;

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

    /**
     * @brief Creates a new instance of the Node class.
     *
     * @return A `std::shared_ptr<Node>` pointing to the newly created instance.
     */
    [[nodiscard]]
    static auto Create() {
        return std::make_shared<Node>();
    }

    template<class T> requires std::is_base_of_v<Node, T>
    [[nodiscard]] auto Is() const {
        return dynamic_cast<const T*>(this) != nullptr;
    }

    template<class T> requires std::is_base_of_v<Node, T>
    [[nodiscard]] auto As() {
        return dynamic_cast<T*>(this);
    }

    template<class T> requires std::is_base_of_v<Node, T>
    [[nodiscard]] auto As() const {
        return dynamic_cast<const T*>(this);
    }

    virtual ~Node() = default;

private:
    /// @brief Flag indicating if children need updating.
    bool update_children_ {false};

    /// @brief Pointer to the parent node.
    Node* parent_ {nullptr};

    /// @brief Unique identifier for this node.
    std::string uuid_ {math::GenerateUUID()};

    /// @brief List of child nodes.
    std::vector<std::shared_ptr<Node>> children_;

    /// @brief Node's local transformation.
    Transform local_transform_;

    /// @brief Node's world transform matrix.
    Matrix4 world_transform_ {1.0f};
};

}