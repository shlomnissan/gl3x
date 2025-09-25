<!-- AUTO-GENERATED — do not edit. -->
# Camera


Abstract base class for camera types.
Not intended for direct use.
## Properties

- `Matrix4 projection_transform`
  - Projection transform.

- `Matrix4 view_transform`
  - View transform.

## Functions

### `GetFrustum()`
  - Returns the cameras frustum.
### `GetNodeType()`
  - Returns node type.
### `GetType()`
  - Returns camera type.
### `LookAt()`
  - Rotates the camera to face a given target position in world space.
### `Resize()`
  - Updates the projection transform to match the new viewport size.
### `SetViewTransform()`
  - Sets the view transform to the inverse of the node's world transform.
### `ViewForward()`
  - Returns the camera's forward axis in view space.
### `ViewRight()`
  - Returns the camera's right axis in view space.
### `ViewUp()`
  - Returns the camera's up axis in view space.
