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

- `float pitch`
   - Default value: `0.0f`
  - Rotation around the X-axis in radians.

- `float roll`
   - Default value: `0.0f`
  - Rotation around the Z-axis in radians.

- `float yaw`
   - Default value: `0.0f`
  - Rotation around the Y-axis in radians.

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
