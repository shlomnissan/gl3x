<!-- AUTO-GENERATED — do not edit. -->
# Transform3


A 3D transformation class supporting translation, scaling, and rotation.
Internally manages position, scale, and rotation in Euler angles. Lazily computes the final transformation matrix when accessed.
## Properties

- `Vector3 position`
   - Default value: `0.0f`
  - World-space translation.

- `Euler rotation`
  - Euler rotation (pitch, yaw, roll).

- `Vector3 scale`
   - Default value: `1.0f`
  - Local scale.

- `bool touched`
   - Default value: `true`
  - Indicates whether the transformation matrix needs to be recomputed.

## Functions

### `Get()`
  - Returns the 4x4 transformation matrix.
### `LookAt()`
  - Sets the rotation such that the object looks at the given target.
### `Rotate()`
  - Applies a rotation around a specific axis.
### `Scale()`
  - Applies a scale to the current scale.
### `SetPosition()`
  - Sets the world position of the transform.
### `SetRotation()`
  - Sets the rotation of the transform.
### `SetScale()`
  - Sets the local scale of the transform.
### `Transform3()`
  - Constructs a Transform3 object with identity transform.
### `Translate()`
  - Applies a translation in local space.
