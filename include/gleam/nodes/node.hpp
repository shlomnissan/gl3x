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
#include "gleam/events/keyboard_event.hpp"
#include "gleam/events/mouse_event.hpp"
#include "gleam/events/scene_event.hpp"
#include "gleam/math/matrix4.hpp"
#include "gleam/math/transform3.hpp"
#include "gleam/math/vector3.hpp"

#include <memory>
#include <vector>

namespace gleam {

/**
 * @brief Represents available node types.
 * @ingroup NodesGroup
 */
enum class NodeType {
    CameraNode,
    DefaultNode,
    LightNode,
    MeshNode,
    SceneNode
};

/**
 * @brief Base class for all scene graph objects.
 *
 * `Node` represents a transformable object that can be placed within a scene
 * graph hierarchy. Nodes support local and world transforms, parent-child
 * relationships, and can respond to events and updates. All renderable,
 * light-emitting, and camera entities in the engine inherit from this class.
 *
 * Nodes can be organized in a tree structure, and transformations will
 * propagate through the hierarchy. When attached to a scene, nodes gain
 * access to the shared context and may perform initialization in `OnAttached()`.
 *
 * To define behavior, override virtual methods such as `OnUpdate()`,
 * `OnKeyboardEvent()`, or `OnMouseEvent()`.
 *
 * @ingroup NodesGroup
 */
class GLEAM_EXPORT Node : public Identity {
public:
    friend class Scene;

    /// @brief Local transformation.
    Transform3 transform;

    /// @brief Local up direction (defaults to +Y).
    Vector3 up {Vector3::Up()};

    /// @brief If true, the local transform is automatically updated before rendering.
    bool transform_auto_update {true};

    /// @brief If true, the node is subject to frustum culling during rendering.
    bool frustum_culled {true};

    /**
     * @brief Adds a child node to this node.
     *
     * @param node Child node to add.
     */
    auto Add(const std::shared_ptr<Node>& node) -> void;

    /**
     * @brief Removes a child node from this node.
     *
     * @param node Child node to remove.
     */
    auto Remove(const std::shared_ptr<Node>& node) -> void;

    /**
     * @brief Removes all children from this node.
     */
    auto RemoveAllChildren() -> void;

    /**
     * @brief Returns the list of child nodes.
     *
     * @return Reference to the vector of child node pointers.
     */
    [[nodiscard]] auto Children() -> std::vector<std::shared_ptr<Node>>&;

    /**
     * @brief Checks whether the given node is a direct child of this node.
     *
     * @param node Pointer to the node to check.
     * @return True if the node is a child.
     */
    [[nodiscard]] auto IsChild(const Node* node) const -> bool;

    /**
     * @brief Returns the parent node.
     *
     * @return Pointer to the parent node, or nullptr if this is a root node.
     */
    [[nodiscard]] auto Parent() const -> const Node*;

    /**
     * @brief Recursively updates this node and all child world transforms.
     *
     * This updates the transformation matrix of the current node first,
     * then propagates the update recursively through all children.
     */
    auto UpdateTransformHierarchy() -> void;

    /**
     * @brief Updates this node’s world transform, ensuring parent transforms are current.
     *
     * This ensures that the world transform of all ancestors is updated before
     * updating the current node. Required for correct world positioning.
     */
    auto UpdateWorldTransform() -> void;

    /**
     * @brief Determines whether the world transform should be recalculated.
     */
    [[nodiscard]] auto ShouldUpdateWorldTransform() const -> bool;

    /**
     * @brief Returns the world-space position of this node.
     */
    [[nodiscard]] auto GetWorldPosition() -> Vector3;

    /**
     * @brief Returns the world transformation matrix of this node.
     */
    [[nodiscard]] auto GetWorldTransform() -> Matrix4;

    /**
     * @brief Returns the shared context associated with this node.
     *
     * The context becomes available once the node is attached to the scene.
     */
    [[nodiscard]] auto Context() const -> SharedContext*;

    /**
     * @brief Returns whether this node is currently attached to a scene.
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
     * @brief Creates a shared pointer to a Node object.
     *
     * @return std::shared_ptr<Node>
     */
    [[nodiscard]] static auto Create() {
        return std::make_shared<Node>();
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~Node() = default;

    /// @name Convenience transformation methods
    /// @{

    /**
     * @brief Rotates the node to face a given target position in world space.
     *
     * @param target Target world-space position to look at.
     */
    auto LookAt(const Vector3& target) -> void;

    /**
     * @brief Translates the node along the X axis in local space.
     * @param value Translation distance.
     */
    auto TranslateX(float value) { transform.Translate({value, 0.0f, 0.0f}); }

    /**
     * @brief Translates the node along the Y axis in local space.
     * @param value Translation distance.
     */
    auto TranslateY(float value) { transform.Translate({0.0f, value, 0.0f}); }

    /**
     * @brief Translates the node along the Z axis in local space.
     * @param value Translation distance.
     */
    auto TranslateZ(float value) { transform.Translate({0.0f, 0.0f, value}); }

    /**
     * @brief Rotates the node along the X axis in local space.
     * @param value Rotation angle in radians.
     */
    auto RotateX(float angle) { transform.Rotate(Vector3::Right(), angle); }

    /**
     * @brief Rotates the node along the Y axis in local space.
     * @param value Rotation angle in radians.
     */
    auto RotateY(float angle) { transform.Rotate(Vector3::Up(), angle); }

    /**
     * @brief Rotates the node along the Z axis in local space.
     * @param value Rotation angle in radians.
     */
    auto RotateZ(float angle) { transform.Rotate(Vector3::Forward(), angle); }

    /**
     * @brief Scales the node uniformly in local space.
     * @param value Scale value.
     */
    auto SetScale(float value) { transform.SetScale({value, value, value}); }

    /**
     * @brief Scales the node non-uniformly in local space.
     *
     * @param value Scale vector applied to the X, Y, and Z axes.
     */
    auto SetScale(const Vector3& value) { transform.SetScale(value); }

    /// @}

    /// @name Event hooks
    /// @{

    /**
     * @brief Called every frame.
     *
     * Override this method to implement per-frame logic or animation.
     *
     * @param delta Time in seconds since the last frame.
     */
    virtual auto OnUpdate(float delta) -> void { /* No-op by default */ }

    /**
     * @brief Called when the node becomes part of an attached scene.
     *
     * This method is invoked when the node is added to a scene that is
     * currently attached to the application context. The shared context is
     * guaranteed to be initialized and available. Use this hook to perform
     * resource loading or event registration that depends on application state.
     */
    virtual auto OnAttached() -> void { /* No-op by default */ }

    /**
     * @brief Called when a keyboard event is dispatched to this node.
     *
     * Override to handle key presses or releases.
     *
     * @param event Pointer to the dispatched keyboard event.
     */
    virtual auto OnKeyboardEvent(KeyboardEvent* event) -> void { /* No-op by default */ }

    /**
     * @brief Called when a mouse event is dispatched to this node.
     *
     * Override to handle mouse movement, clicks, or scrolling.
     *
     * @param event Pointer to the dispatched mouse event.
     */
    virtual auto OnMouseEvent(MouseEvent* event) -> void { /* No-op by default */ }

    /// @}

private:
    std::vector<std::shared_ptr<Node>> children_;

    SharedContext* context_ {nullptr};

    Node* parent_ {nullptr};

    Matrix4 world_transform_ {1.0f};

    bool world_transform_touched_ {false};

    auto AttachRecursive(SharedContext* context) -> void;

    auto DetachRecursive() -> void;
};

}