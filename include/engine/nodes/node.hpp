// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "engine_export.h"
#include "engine/core/identity.hpp"
#include "engine/math/matrix4.hpp"
#include "engine/math/transform_3d.hpp"
#include "engine/math/vector3.hpp"

#include <memory>
#include <vector>

namespace engine {

struct KeyboardEvent; ///< Forward declaration
struct MouseEvent; ///< Forward declaration

/**
 * @brief Represents a node in a scene graph.
 */
class ENGINE_EXPORT Node : public Identity {
public:
    /// @brief Node's local transformation.
    Transform3D transform;

    /// @brief The up vector of the node.
    Vector3 up {Vector3::Up()};

    /// @brief The current level in the scene graph.
    int level {0};

    /// @brief Flag indicating whether the transform should be automatically updated.
    bool transformAutoUpdate {true};

    /// @brief Flag indicating whether the node is culled by the view frustum.
    bool frustumCulled {true};

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
     * @brief Removes all child nodes from this node.
     */
    auto RemoveAllChildren() -> void;

    /**
     * @brief Retrieves the list of child nodes.
     *
     * @return A reference to a vector of child nodes.
     */
    [[nodiscard]] auto Children() -> std::vector<std::shared_ptr<Node>>&;

    /**
     * @brief Retrieves the parent node of this node.
     *
     * @return A pointer to the parent node. If this node has no parent, the return value will be a null pointer.
     */
    [[nodiscard]] auto Parent() const -> const Node*;

    /**
     * @brief Updates the transformation matrix of this node and all its child nodes.
     *
     * This function updates the transformation matrix of the current node first,
     * and then recursively updates the transformation matrices of all child nodes.
     * This ensures that the entire transformation hierarchy is updated correctly.
     */
    auto UpdateTransformHierarchy() -> void;

    /**
     * @brief Updates the world transform of this node and all its parent nodes.
     *
     * This function ensures that the world transform of all parent nodes is updated
     * before updating the world transform of this node. This is necessary to maintain
     * the correct transformation hierarchy when fetching the current world position.
     */
    auto UpdateWorldTransform() -> void;

    /**
     * @brief Determines if the node's world transform should be updated.
     *
     * @return True if the transform was modified or the parent requires an update.
     */
    [[nodiscard]] auto ShouldUpdateWorldTransform() const -> bool;

    /**
     * @brief Retrieves the world position of the node.
     *
     * @return The world position of the node.
     */
    [[nodiscard]] auto GetWorldPosition() -> Vector3;

    /**
     * @brief Retrieves the world transformation matrix of the node.
     *
     * @return The world transformation matrix of the node.
     */
    [[nodiscard]] auto GetWorldTransform() const -> Matrix4 {
        return world_transform_;
    }

    /**
     * @brief Rotates the object to face a point in world space.
     *
     * @param target The target position to look at.
     */
    auto LookAt(const Vector3& target) -> void;

    /**
     * @brief Creates a new instance of the Node class.
     *
     * @return A `std::shared_ptr<Node>` pointing to the newly created instance.
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Node>();
    }

    /**
     * @brief Checks if the current node is of the specified type.
     *
     * @tparam T The type to check against, which must be derived from Node.
     * @return True if the node is of type T, otherwise false.
     */
    template<class T> requires std::is_base_of_v<Node, T>
    [[nodiscard]] auto Is() const {
        return dynamic_cast<const T*>(this) != nullptr;
    }

    /**
     * @brief Casts the current node to the specified type.
     *
     * @tparam T The type to cast to, which must be derived from Node.
     * @return A pointer to the node cast to type T, or nullptr if the cast fails.
     */
    template<class T> requires std::is_base_of_v<Node, T>
    [[nodiscard]] auto As() {
        return dynamic_cast<T*>(this);
    }

    /**
     * @brief Casts the current node to the specified type (const version).
     *
     * @tparam T The type to cast to, which must be derived from Node.
     * @return A constant pointer to the node cast to type T, or nullptr if the cast fails.
    */
    template<class T> requires std::is_base_of_v<Node, T>
    [[nodiscard]] auto As() const {
        return dynamic_cast<const T*>(this);
    }

    /**
     * @brief Default destructor.
     */
    virtual ~Node() = default;

    #pragma region Transformations

    /**
     * @brief Translates the node along the X-axis.
     *
     * @param value The amount to translate the node.
     */
    auto TranslateX(float value) { transform.Translate({value, 0.0f, 0.0f}); }

    /**
     * @brief Translates the node along the Y-axis.
     *
     * @param value The amount to translate the node.
     */
    auto TranslateY(float value) { transform.Translate({0.0f, value, 0.0f}); }

    /**
     * @brief Translates the node along the Z-axis.
     *
     * @param value The amount to translate the node.
     */
    auto TranslateZ(float value) { transform.Translate({0.0f, 0.0f, value}); }

    /**
     * @brief Rotates the node around the X-axis.
     *
     * @param value The angle to rotate the node.
     */
    auto RotateX(float angle) { transform.Rotate(Vector3::Right(), angle); }

    /**
     * @brief Rotates the node around the Y-axis.
     *
     * @param value The angle to rotate the node.
     */
    auto RotateY(float angle) { transform.Rotate(Vector3::Up(), angle); }

    /**
     * @brief Rotates the node around the Z-axis.
     *
     * @param value The angle to rotate the node.
     */
    auto RotateZ(float angle) { transform.Rotate(Vector3::Forward(), angle); }

    /**
     * @brief Set a uniform scale for the node.
     *
     * @param value The amount to scale the node.
     */
    auto SetScale(float value) { transform.SetScale({value, value, value}); }

    /**
     * @brief Set a scale for the node.
     *
     * @param value The amount to scale the node.
     */
    auto SetScale(const Vector3& value) { transform.SetScale(value); }

    #pragma endregion

    #pragma region Events

    /**
     * @brief Invoked before rendering the node.
     */
    virtual auto Update(float delta) -> void { /* No-op by default */ }

    /**
     * @brief Invoked when a keyboard event is received.
     *
     * @param event A pointer to the keyboard event.
     */
    virtual auto OnKeyboardEvent(KeyboardEvent* event) -> void { /* No-op by default */ }

    /**
     * @brief Invoked when a mouse event is received.
     *
     * @param event A pointer to the mouse event.
     */
    virtual auto OnMouseEvent(MouseEvent* event) -> void { /* No-op by default */ }

    #pragma endregion

private:
    /// @brief List of child nodes.
    std::vector<std::shared_ptr<Node>> children_;

    /// @brief Pointer to the parent node.
    Node* parent_ {nullptr};

    /// @brief Node's world transformation.
    Matrix4 world_transform_ {1.0f};

    /// @brief Flag indicating whether the world transform was modified.
    bool world_transform_touched_ {false};

    /**
     * @brief Updates the level of the specified child node.
     *
     * @param node A shared pointer to the child node whose level is to be updated.
     */
    auto UpdateLevel(const std::shared_ptr<Node>& node) -> void;
};

}