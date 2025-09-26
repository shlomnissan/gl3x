<!-- AUTO-GENERATED — do not edit. -->
# Transform2


A 2D transformation class supporting translation, scaling, and rotation.
Internally manages position, scale, rotation, and center of transformation. Lazily computes the final transformation matrix when accessed.
## Properties

<div class="property">
  <div class="definition">
    <span class="name">center</span> <span class="type">Vector2</span>
  </div>
  <div class="description">
    Pivot for rotation and scaling.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">position</span> <span class="type">Vector2</span>
  </div>
  <div class="description">
    World-space translation.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">rotation</span> <span class="type">float</span>
  </div>
  <div class="description">
    Rotation angle in radians.
  </div>
</div>

<div class="property">
  <div class="definition">
    <span class="name">scale</span> <span class="type">Vector2</span>
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
  - Returns the 3x3 transformation matrix.
### `Rotate()`
  - Applies a rotation delta to the current rotation.
### `Scale()`
  - Applies a scale to the current scale.
### `SetCenter()`
  - Sets the pivot point for rotation and scaling.
### `SetPosition()`
  - Sets the world position of the transform.
### `SetRotation()`
  - Sets the rotation angle of the transform.
### `SetScale()`
  - Sets the local scale of the transform.
### `Transform2()`
  - Constructs a Transform2 object with identity transform.
### `Translate()`
  - Applies a translation in local space.
