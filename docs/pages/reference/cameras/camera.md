<!-- AUTO-GENERATED — do not edit. -->
# Camera


Abstract base class for camera types.
This class is not intended to be used directly. Use PerspectiveCamera or OrthographicCamera unless you are defining your own camera type, in which case it should inherit from this class.
## Properties

<div class="property">
  <div class="definition">
    <span class="name">projection_matrix</span> <span class="type">Matrix4</span>
  </div>
  <div class="description">
    Projection matrix that maps camera-space coordinates to clip space.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">view_matrix</span> <span class="type">Matrix4</span>
  </div>
  <div class="description">
    View matrix (inverse of the camera’s world transform) that maps world space to camera space.
  </div>
</div>

## Functions

### `Forward()`
  - Camera forward axis in world space.
### `GetFrustum()`
  - Computes a Frustum from the combined projection and view matrices.
### `GetNodeType()`
  - Identifies this node as a camera.
### `LookAt()`
  - Overrides Node::LookAt to orient the camera toward a world-space target.
### `Resize()`
  - Updates projection_matrix to reflect the current viewport size.
### `Right()`
  - Camera right axis in world space.
### `Up()`
  - Camera up axis in world space.
### `UpdateViewMatrix()`
  - Sets view_matrix to the inverse of the camera's world transform.
