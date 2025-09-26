<!-- AUTO-GENERATED — do not edit. -->
# Node


Base class for all scene graph objects.
`Node` represents a transformable object that can be placed within a scene graph hierarchy. Nodes support local and world transforms, parent-child relationships, and can respond to events and updates. All renderable, light-emitting, and camera entities in the engine inherit from this class.

Nodes can be organized in a tree structure, and transformations will propagate through the hierarchy. When attached to a scene, nodes gain access to the shared context and may perform initialization in `OnAttached(SharedContextPointer context)`.

To define behavior, override virtual methods such as `OnUpdate()`, `OnKeyboardEvent()`, or `OnMouseEvent()`.
## Constructors

### `Node()`
Constructs an Node instance.

## Properties

<div class="property">
  <div class="definition">
    <span class="name">frustum_culled</span> <span class="type">bool</span>
  </div>
  <div class="description">
    If true, the node is subject to frustum culling during rendering.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">transform</span> <span class="type">Transform3</span>
  </div>
  <div class="description">
    Local transformation.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">transform_auto_update</span> <span class="type">bool</span>
  </div>
  <div class="description">
    If true, the local transform is automatically updated before rendering.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">up</span> <span class="type">Vector3</span>
  </div>
  <div class="description">
    Local up direction (defaults to +Y).
  </div>
</div>

## Functions

### `LookAt()`
  - Rotates the node to face a given target position in world space.
### `TranslateX()`
  - Translates the node along the X axis in local space.
### `TranslateY()`
  - Translates the node along the Y axis in local space.
### `TranslateZ()`
  - Translates the node along the Z axis in local space.
### `RotateX()`
  - Rotates the node along the X axis in local space.
### `RotateY()`
  - Rotates the node along the Y axis in local space.
### `RotateZ()`
  - Rotates the node along the Z axis in local space.
### `SetScale()`
  - Scales the node non-uniformly in local space.
### `OnUpdate()`
  - Called every frame.
### `OnAttached()`
  - Called when the node becomes part of an attached scene.
### `OnKeyboardEvent()`
  - Called when a keyboard event is dispatched to this node.
### `OnMouseEvent()`
  - Called when a mouse event is dispatched to this node.
### `Add()`
  - Adds a child node to this node.
### `Children()`
  - Returns the list of child nodes.
### `GetNodeType()`
  - Returns node type.
### `GetWorldPosition()`
  - Returns the world-space position of this node.
### `GetWorldTransform()`
  - Returns the world transformation matrix of this node.
### `IsChild()`
  - Checks whether the given node is a direct child of this node.
### `IsRenderable()`
  - Returns true if the node is renderable.
### `Parent()`
  - Returns the parent node.
### `Remove()`
  - Removes a child node from this node.
### `RemoveAllChildren()`
  - Removes all children from this node.
### `ShouldUpdateWorldTransform()`
  - Determines whether the world transform should be recalculated.
### `UpdateTransformHierarchy()`
  - Recursively updates this node and all child world transforms.
### `UpdateWorldTransform()`
  - Updates this node’s world transform, ensuring parent transforms are current.
### `Create()`
  - Creates a shared pointer to a Node object.
