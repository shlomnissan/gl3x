<!-- AUTO-GENERATED — do not edit. -->
# Euler


Represents 3D Euler angles with pitch, yaw, and roll components.
`Euler` stores orientation using intrinsic Tait-Bryan angles in **YXZ order**, where:**yaw** is a rotation around the Y-axis,**pitch** is a rotation around the X-axis,**roll** is a rotation around the Z-axis.

**yaw** is a rotation around the Y-axis,

**pitch** is a rotation around the X-axis,

**roll** is a rotation around the Z-axis.

This class supports construction from individual angles or a transformation matrix, and can convert back to a `Matrix4` representation for use in transformations.

Note: Gimbal lock may occur when pitch approaches ±90°, limiting the reliability of angle reconstruction.
## Properties

<div class="property">
  <div class="definition">

  ### <span class="name">pitch</span> <span class="type">float</span>
  ```cpp
  float pitch { 0.0f }
  ```
  </div>
  <div class="description">
    Rotation around the X-axis in radians.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">roll</span> <span class="type">float</span>
  ```cpp
  float roll { 0.0f }
  ```
  </div>
  <div class="description">
    Rotation around the Z-axis in radians.
  </div>
</div>

<div class="property">
  <div class="definition">

  ### <span class="name">yaw</span> <span class="type">float</span>
  ```cpp
  float yaw { 0.0f }
  ```
  </div>
  <div class="description">
    Rotation around the Y-axis in radians.
  </div>
</div>

## Functions

### `Euler()`
  - Constructs an Euler angles object.
### `Euler()`
  - Constructs an Euler angles object from a transformation matrix.
### `Euler()`
  - Constructs an Euler angles object from pitch, yaw, and roll.
### `GetMatrix()`
  - Converts the Euler angles into a 4×4 transformation matrix.
### `IsEmpty()`
  - Checks whether all angles are zero.
