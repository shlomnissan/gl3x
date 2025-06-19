/*
===========================================================================
  GLEAM ENGINE https://gleamengine.org
  Copyright © 2024 - Present, Shlomi Nissan
===========================================================================
*/

#pragma once

#include "gleam_export.h"
#include "gleam/core/identity.hpp"
#include "gleam/core/shared_context.hpp"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/transform3.hpp"
#include "gleam/math/vector3.hpp"

#include <memory>
#include <vector>

namespace gleam {

// Forward declarations
struct KeyboardEvent;
struct MouseEvent;

/**
 * @brief Represents available node types.
 */
enum class NodeType {
    CameraNode,
    DefaultNode,
    LightNode,
    MeshNode,
    SceneNode
};

/**
 * @brief Represents a node in a scene graph.
 */
class GLEAM_EXPORT Node : public Identity {
public:
    /// @brief Node's local transformation.
    Transform3 transform;

    /// @brief The up vector of the node.
    Vector3 up {Vector3::Up()};

    /// @brief Flag indicating whether the transform should be automatically updated.
    bool transform_auto_update {true};

    /// @brief Flag indicating whether the node is culled by the view frustum.
    bool frustum_culled {true};

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
     * @brief Checks if the specified node is a child of this node.
     *
     * @param node A pointer to the node to check.
     * @return True if the node is a child of this node, otherwise false.
     */
    [[nodiscard]] auto IsChild(const Node* node) const -> bool;

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
    [[nodiscard]] auto GetWorldTransform() -> Matrix4;

    /**
     * @brief Retrieves the shared context of the node. If the context is not
     * set, an error log is generated and a null pointer is returned.
     *
     * @return A pointer to the shared context.
     */
    [[nodiscard]] auto Context() const -> SharedContext*;

    /**
     * @brief Returns whether the node is attached to an active scene.
     * An active scene is one that has been attached to the application context.
     */
    [[nodiscard]] auto IsAttached() const {
        return context_ != nullptr;
    }

    /**
     * @brief Returns node type.
     *
     * @return NodeType::DefaultNode
     */
    [[nodiscard]] virtual auto GetNodeType() const -> NodeType {
        return NodeType::DefaultNode;
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
     * @param value The angle to rotate by in radians.
     */
    auto RotateX(float angle) { transform.Rotate(Vector3::Right(), angle); }

    /**
     * @brief Rotates the node around the Y-axis.
     *
     * @param value The angle to rotate by in radians.
     */
    auto RotateY(float angle) { transform.Rotate(Vector3::Up(), angle); }

    /**
     * @brief Rotates the node around the Z-axis.
     *
     * @param value The angle to rotate by in radians.
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
    virtual auto OnUpdate(float delta) -> void { /* No-op by default */ }

    /**
     * @brief Called when the node is attached to an active scene.
     *
     * This method is invoked when the node becomes part of a scene that is
     * attached to the application context. At this point, the shared context
     * is guaranteed to be initialized and accessible. Override this method
     * to perform any setup or initialization that depends on the shared context
     * such as loading resources or setting up event listeners.
     */
    virtual auto OnAttached() -> void { /* No-op by default */ }

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
    /// @brief The scene sets the node's shared context.
    friend class Scene;

    /// @brief List of child nodes.
    std::vector<std::shared_ptr<Node>> children_;

    /// @brief The shared context for the scene.
    SharedContext* context_ {nullptr};

    /// @brief Pointer to the parent node.
    Node* parent_ {nullptr};

    /// @brief Node's world transformation.
    Matrix4 world_transform_ {1.0f};

    /// @brief Flag indicating whether the world transform was modified.
    bool world_transform_touched_ {false};

    /**
     * @brief Recursively attaches the node and its children to the shared context.
     *
     * This method is called when the node is added to a scene. It ensures that the
     * shared context is propagated to the node and all of its child nodes.
     *
     * @param context A pointer to the shared context to attach to the node and its children.
     */
    auto AttachRecursive(SharedContext* context) -> void;

    /**
     * @brief Recursively detaches the node and its children from the shared context.
     *
     * This method is called when the node is removed from a scene. It ensures that the
     * shared context is cleared for the node and all of its child nodes, effectively
     * disconnecting them from the scene's shared resources.
     */
    auto DetachRecursive() -> void;
};

}