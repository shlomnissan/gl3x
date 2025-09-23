<!-- AUTO-GENERATED — do not edit. -->
# Euler


Represents 3D Euler angles with pitch, yaw, and roll components.
`Euler` stores orientation using intrinsic Tait-Bryan angles in **YXZ order**, where:**yaw** is a rotation around the Y-axis,**pitch** is a rotation around the X-axis,**roll** is a rotation around the Z-axis.

**yaw** is a rotation around the Y-axis,

**pitch** is a rotation around the X-axis,

**roll** is a rotation around the Z-axis.

This class supports construction from individual angles or a transformation matrix, and can convert back to a `Matrix4` representation for use in transformations.

Note: Gimbal lock may occur when pitch approaches ±90°, limiting the reliability of angle reconstruction.
