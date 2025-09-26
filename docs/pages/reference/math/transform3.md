<!-- AUTO-GENERATED — do not edit. -->
# Transform3


A 3D transformation class supporting translation, scaling, and rotation.
Internally manages position, scale, and rotation in Euler angles. Lazily computes the final transformation matrix when accessed.
## Properties

<div class="property">
  <div class="definition">
    <span class="name">position</span> <span class="type">Vector3</span>
  </div>
  <div class="description">
    World-space translation.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">rotation</span> <span class="type">Euler</span>
  </div>
  <div class="description">
    Euler rotation (pitch, yaw, roll).
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">scale</span> <span class="type">Vector3</span>
  </div>
  <div class="description">
    Local scale.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">touched</span> <span class="type">bool</span>
  </div>
  <div class="description">
    Indicates whether the transformation matrix needs to be recomputed.
  </div>
</div>

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
