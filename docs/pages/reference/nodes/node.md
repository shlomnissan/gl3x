<!-- AUTO-GENERATED — do not edit. -->
# Node


Base class for all scene graph objects.
`Node` represents a transformable object that can be placed within a scene graph hierarchy. Nodes support local and world transforms, parent-child relationships, and can respond to events and updates. All renderable, light-emitting, and camera entities in the engine inherit from this class.

Nodes can be organized in a tree structure, and transformations will propagate through the hierarchy. When attached to a scene, nodes gain access to the shared context and may perform initialization in `OnAttached(SharedContextPointer context)`.

To define behavior, override virtual methods such as `OnUpdate()`, `OnKeyboardEvent()`, or `OnMouseEvent()`.
## Properties

- `bool frustum_culled`
   - Default value: `true`
  - If true, the node is subject to frustum culling during rendering.

- `Transform3 transform`
  - Local transformation.

- `bool transform_auto_update`
   - Default value: `true`
  - If true, the local transform is automatically updated before rendering.

- `Vector3 up`
   - Default value: `Vector3::Up()`
  - Local up direction (defaults to +Y).
